// vulkan
#include "fillcan/shader/descriptor_pool.hpp"
#include "fillcan/shader/descriptor_pool_builder.hpp"
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "fillcan/shader/descriptor_set_layout_builder.hpp"
#include "fillcan/shader/shader_module.hpp"
#include "vulkan/vulkan_core.h"

#include "app.hpp"

// fillcan
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>

// std
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace app {
    App::App() {}
    App::~App() {}

    void App::run() {
        std::string name = "Default Application";
        std::cout << "Running App \"" << name << "\"\n";
        upFillcan = std::make_unique<fillcan::Fillcan>(name.c_str(), 1.0, 800, 600, (VkPhysicalDeviceFeatures){.samplerAnisotropy = true});

        // Select any device
        fillcan::LogicalDevice* currentDevice = upFillcan->selectDevice(0);

        fillcan::CommandRecording graphicsRecording = currentDevice->getGraphicsQueue()->createRecording(2, 1);
        fillcan::CommandRecording graphicsRecording2 = currentDevice->getGraphicsQueue()->createRecording(1, 1);
        fillcan::CommandRecording presentRecording = currentDevice->getPresentQueue()->createRecording(2, 1);
        fillcan::CommandRecording computRecording = currentDevice->getComputeQueue()->createRecording(2, 1);

        for (std::shared_ptr<fillcan::CommandBuffer>& pCommandBuffer : graphicsRecording.pPrimaryCommandBuffers) {
            std::cout << pCommandBuffer->begin() << "\n";
        }
        for (std::shared_ptr<fillcan::CommandBuffer>& pCommandBuffer : graphicsRecording.pSecondaryCommandBuffers) {
            VkCommandBufferInheritanceInfo test = {.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO};
            std::cout << pCommandBuffer->begin(0, &test) << "\n";
        }
        std::cout << graphicsRecording.endAll() << "\n";
        currentDevice->getGraphicsQueue()->submitRecordings({&graphicsRecording}, nullptr);
        currentDevice->getGraphicsQueue()->waitIdle();
        graphicsRecording.resetAll();
        currentDevice->getGraphicsQueue()->freeRecording(graphicsRecording);

        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> descriptorSetLayouts = {};

        fillcan::DescriptorSetLayoutBuilder descriptorSetLayoutBuilder{};
        descriptorSetLayoutBuilder.setLogicalDevice(currentDevice);
        descriptorSetLayoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);
        descriptorSetLayouts.push_back(descriptorSetLayoutBuilder.getResult());

        descriptorSetLayoutBuilder.reset();
        descriptorSetLayoutBuilder.setLogicalDevice(currentDevice);
        descriptorSetLayoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);
        descriptorSetLayouts.push_back(descriptorSetLayoutBuilder.getResult());

        // descriptorSetLayouts.push_back(std::move(layout1));

        fillcan::DescriptorPoolBuilder descriptorPoolBuilder = fillcan::DescriptorPoolBuilder();
        descriptorPoolBuilder.setLogicalDevice(currentDevice);
        descriptorPoolBuilder.setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
        descriptorPoolBuilder.addSet(descriptorSetLayouts[0].get(), 3);
        descriptorPoolBuilder.addSet(descriptorSetLayouts[1].get(), 1);
        std::unique_ptr<fillcan::DescriptorPool> pool = descriptorPoolBuilder.getResult();
        std::cout << (pool->freeDescriptorSets() ? "Freed descriptor sets" : "Failed to free descriptor sets") << "\n";
        std::cout << (pool->reset() ? "Reset pool" : "Failed to reset pool") << "\n";

        fillcan::ShaderModule shaderModule = fillcan::ShaderModule("", std::move(descriptorSetLayouts), std::move(pool));

        upFillcan->MainLoop(std::bind(&App::update, this));
    }

    void App::update() {}
} // namespace app