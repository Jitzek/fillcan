#include "app.hpp"
#include "fillcan/memory/fence.hpp"
#include "glm/detail/precision.hpp"
#include "shaderc/shaderc.h"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/memory.hpp>

#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_pool_builder.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/descriptor_set_layout_builder.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/shader_module.hpp>

#include <fillcan/computing/compute_pipeline.hpp>
#include <fillcan/computing/compute_pipeline_builder.hpp>

#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/commands/command_recording.hpp>

// std
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

// glm
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace compute_pipeline {
    App::App() {}
    App::~App() {}

    struct Config {
        int transform;
        int integerCount;
    };

    struct InputBuffer {
        int integers[4096];
    };

    struct OutputBuffer {
        int integers[4096];
    };

    void App::run() {
        std::string name = "Compute Pipeline Test Application";
        std::cout << "Running App \"" << name << "\"\n";

        /*
            Instance Fillcan
        */
        VkPhysicalDeviceFeatures requiredDeviceFeatures = {};
        upFillcan = std::make_unique<fillcan::Fillcan>(name.c_str(), 1.0, requiredDeviceFeatures);

        // Select any device
        upFillcan->selectDevice(0);

        std::cout << "Using Device: " << upFillcan->getCurrentDevice()->getPhysicalDevice()->getProperties().deviceName << "\n";
        /* */

        /*
            Create the descriptor set layouts to bind the needed uniform buffer and two storage buffers
        */
        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> upDescriptorSetLayouts = this->createDescriptorSetLayouts();
        /* */

        /*
            Create a descriptor pool with the descriptor set layouts, descriptor sets will be automatically allocated
        */
        std::unique_ptr<fillcan::DescriptorPool> upDescriptorPool = this->createDescriptorPool(upDescriptorSetLayouts);
        /* */

        /*
            Create resources to bind to the descriptor sets
        */
        // Create one uniform buffer
        fillcan::BufferDirector bufferDirector{};
        std::unique_ptr<fillcan::Buffer> upUniformBufferConfig =
            bufferDirector.makeUniformBuffer(this->upFillcan->getCurrentDevice(), sizeof(Config));

        // Create two storage buffers
        std::unique_ptr<fillcan::Buffer> upStorageBufferInputBuffer =
            bufferDirector.makeStorageBuffer(this->upFillcan->getCurrentDevice(), sizeof(InputBuffer));

        std::unique_ptr<fillcan::Buffer> upStorageBufferOutputBuffer =
            bufferDirector.makeStorageBuffer(this->upFillcan->getCurrentDevice(), sizeof(OutputBuffer));
        /* */

        /*
            Bind memory to resources
        */
        fillcan::Memory uniformBufferConfigMemory =
            fillcan::Memory(this->upFillcan->getCurrentDevice(), upUniformBufferConfig.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        fillcan::Memory storageBufferInputBufferMemory =
            fillcan::Memory(this->upFillcan->getCurrentDevice(), upStorageBufferInputBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        fillcan::Memory storageBufferOutputBufferMemory =
            fillcan::Memory(this->upFillcan->getCurrentDevice(), upStorageBufferOutputBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

        upUniformBufferConfig->bindMemory(&uniformBufferConfigMemory);
        upStorageBufferInputBuffer->bindMemory(&storageBufferInputBufferMemory);
        upStorageBufferOutputBuffer->bindMemory(&storageBufferOutputBufferMemory);
        /* */

        /*
            Bind resources to descriptor sets
        */
        // std::vector<fillcan::DescriptorSet*> pDescriptorSets = upDescriptorPool->getDescriptorSets();
        fillcan::DescriptorSet* pDescriptorSet = upDescriptorPool->getDescriptorSet("ComputeDescriptorSet");
        // We created one descriptor set layout for all bindings
        fillcan::DescriptorSetLayout* pDescriptorSetLayout = upDescriptorSetLayouts[0].get();
        pDescriptorSet->writeBuffer(pDescriptorSetLayout->getBindings()[0], upUniformBufferConfig.get());
        pDescriptorSet->writeBuffer(pDescriptorSetLayout->getBindings()[1], upStorageBufferInputBuffer.get());
        pDescriptorSet->writeBuffer(pDescriptorSetLayout->getBindings()[2], upStorageBufferOutputBuffer.get());
        /* */

        /*
            Create Shader Module
        */
        std::unique_ptr<fillcan::ShaderModule> upComputeShaderModule =
            this->upFillcan->createShaderModule(this->APP_DIR + "/shaders", "compute-shader.comp", shaderc_compute_shader,
                                                std::move(upDescriptorSetLayouts), std::move(upDescriptorPool));
        /* */

        /*
            Create Compute Pipeline
        */
        this->createComputePipeline({
            .stage = VK_SHADER_STAGE_COMPUTE_BIT,
            .pShaderModule = upComputeShaderModule.get(),
            .name = "main",
        });
        /* */

        /*
            Map the memory
        */
        void** ppConfigData = uniformBufferConfigMemory.map();
        void** ppInputData = storageBufferInputBufferMemory.map();
        void** ppOutputData = storageBufferOutputBufferMemory.map();
        /* */

        /*
            Fill buffers with data
        */
        int integerCount = 4096;

        Config config = {.transform = 10, .integerCount = integerCount};
        memcpy(*ppConfigData, &config, sizeof(config));

        InputBuffer inputBuffer = {.integers = {}};
        for (int i = 0; i < integerCount; i++) {
            inputBuffer.integers[i] = i;
        }
        memcpy(*ppInputData, &inputBuffer, sizeof(inputBuffer));

        // Flush memory because the host has changed it
        uniformBufferConfigMemory.flush();
        storageBufferInputBufferMemory.flush();
        /* */

        /*
            Record commands
        */
        std::cout << "Transforming " << (*reinterpret_cast<Config*>(*ppConfigData)).integerCount << " integers with "
                  << (*reinterpret_cast<Config*>(*ppConfigData)).transform << "\n";

        std::cout << "Input Data: \n";
        for (int i : (*reinterpret_cast<InputBuffer*>(*ppInputData)).integers) {
            std::cout << i << " ";
            if (i % 16 == 0) {
                std::cout << "\n";
            }
        }
        std::cout << "\n\n";

        // Create recording to gain access to a primary commandbuffer
        fillcan::CommandRecording* pComputeCommandRecording = upFillcan->getCurrentDevice()->getComputeQueue()->createRecording(1, 0);
        fillcan::CommandBuffer* pComputePrimaryCommandBuffer = pComputeCommandRecording->pPrimaryCommandBuffers[0];

        // Begin compute recording commands
        pComputePrimaryCommandBuffer->begin();
        this->upComputePipeline->bindToCommandBuffer(pComputePrimaryCommandBuffer);
        this->upComputePipeline->bindDescriptorSets();
        // this->upComputePipeline->start();
        int groupCount = ((integerCount) / 256) + 1;
        vkCmdDispatch(pComputePrimaryCommandBuffer->getCommandBufferHandle(), groupCount, 1, 1);
        pComputePrimaryCommandBuffer->end();

        // Create Fence
        fillcan::Fence computeFence = fillcan::Fence(this->upFillcan->getCurrentDevice());
        // Submit command buffers
        this->upFillcan->getCurrentDevice()->getComputeQueue()->submitRecordings({pComputeCommandRecording}, &computeFence);
        // Wait for command buffers to finish
        computeFence.waitFor();

        // Invalidate buffer memory because the device has changed it
        storageBufferOutputBufferMemory.invalidate();

        std::cout << "Output Data: \n";
        for (int i : (*reinterpret_cast<InputBuffer*>(*ppOutputData)).integers) {
            std::cout << i << " ";
            if (i % 16 == 0) {
                std::cout << "\n";
            }
        }
        std::cout << "\n";
        /* */
    }

    void App::update() {}

    std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> App::createDescriptorSetLayouts() {
        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> upDescriptorSetLayouts;
        upDescriptorSetLayouts.reserve(1);

        fillcan::DescriptorSetLayoutBuilder descriptorSetLayoutBuilder{};
        descriptorSetLayoutBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());

        // Config
        descriptorSetLayoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);

        // InputBuffer
        descriptorSetLayoutBuilder.addBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);

        // OutputBuffer
        descriptorSetLayoutBuilder.addBinding(2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);

        upDescriptorSetLayouts.emplace_back(descriptorSetLayoutBuilder.getResult());

        return std::move(upDescriptorSetLayouts);
    }

    std::unique_ptr<fillcan::DescriptorPool>
    App::createDescriptorPool(std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>>& upDescriptorSetLayouts) {
        fillcan::DescriptorPoolBuilder descriptorPoolBuilder{};
        descriptorPoolBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        descriptorPoolBuilder.setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
        descriptorPoolBuilder.addSet(upDescriptorSetLayouts.at(0).get(), "ComputeDescriptorSet");
        return std::move(descriptorPoolBuilder.getResult());
    }

    void App::createComputePipeline(fillcan::PipelineShaderStage pipelineShaderStage) {
        fillcan::ComputePipelineBuilder computePipelineBuilder{};
        computePipelineBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        computePipelineBuilder.setFlags(0);
        computePipelineBuilder.setBasePipeline(nullptr);
        computePipelineBuilder.setShaderStage(pipelineShaderStage);
        this->upComputePipeline = computePipelineBuilder.getResult();
    }
} // namespace compute_pipeline