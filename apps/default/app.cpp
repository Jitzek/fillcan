// vulkan
#include "vulkan/vulkan_core.h"

#include "app.hpp"

// fillcan
#include <cstring>
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/buffer_view.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_director.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/memory/memory.hpp>
#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_pool_builder.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/descriptor_set_layout_builder.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace app {
    App::App() {}
    App::~App() {}

    struct TestBufferData {
        std::string value;
    };

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
        descriptorSetLayoutBuilder.addBinding(1, VK_DESCRIPTOR_TYPE_SAMPLER, 2, VK_SHADER_STAGE_COMPUTE_BIT);
        descriptorSetLayouts.push_back(descriptorSetLayoutBuilder.getResult());

        fillcan::DescriptorPoolBuilder descriptorPoolBuilder = fillcan::DescriptorPoolBuilder();
        descriptorPoolBuilder.setLogicalDevice(currentDevice);
        descriptorPoolBuilder.setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
        descriptorPoolBuilder.addSet(descriptorSetLayouts[0].get(), 3);
        descriptorPoolBuilder.addSet(descriptorSetLayouts[1].get(), 1);
        std::unique_ptr<fillcan::DescriptorPool> descriptorPool = descriptorPoolBuilder.getResult();
        std::cout << (descriptorPool->freeDescriptorSets() ? "Freed descriptor sets" : "Failed to free descriptor sets") << "\n";
        std::cout << (descriptorPool->reset() ? "Reset pool" : "Failed to reset pool") << "\n";

        std::vector<char> code = {'t', 'e', 's', 't'};
        fillcan::ShaderModule shaderModule = fillcan::ShaderModule(currentDevice, code, std::move(descriptorSetLayouts), std::move(descriptorPool));

        fillcan::BufferDirector bufferDirector = fillcan::BufferDirector();
        std::unique_ptr<fillcan::Buffer> buffer1 = bufferDirector.makeUniformTexelBuffer(currentDevice, 4);
        fillcan::Memory memory1 = fillcan::Memory(currentDevice, buffer1.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        std::cout << memory1.getMemoryHandle() << "\n";

        fillcan::ImageDirector imageDirector = fillcan::ImageDirector();
        std::unique_ptr<fillcan::Image> image1 = imageDirector.make2DTexture(currentDevice, 10, 10, VK_SAMPLE_COUNT_1_BIT);
        fillcan::Memory memory2 = fillcan::Memory(currentDevice, image1.get(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        std::cout << memory2.getMemoryHandle() << "\n";

        void** ppData = memory1.map();
        TestBufferData testBufferData1 = {.value = "Hello World from Buffer!"};
        memcpy(*ppData, &testBufferData1, sizeof(testBufferData1));
        memory1.flush();
        std::cout << (*reinterpret_cast<TestBufferData*>(*ppData)).value << "\n";

        buffer1->bindMemory(&memory1);
        image1->bindMemory(&memory2);

        std::cout << buffer1->createBufferView(VK_FORMAT_R8G8B8A8_UNORM)->getBufferViewHandle() << "\n";
        std::cout << buffer1->getBufferViews()[0]->getBufferViewHandle() << "\n";

        std::cout << image1->createImageView(VK_IMAGE_VIEW_TYPE_2D, VK_FORMAT_R8G8B8A8_SRGB)->getImageViewHandle() << "\n";
        std::cout << image1->getImageViews()[0]->getImageViewHandle() << "\n";

        upFillcan->MainLoop(std::bind(&App::update, this));
    }

    void App::update() {}
} // namespace app