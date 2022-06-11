// vulkan
#include "vulkan/vulkan_core.h"

#include "app.hpp"

// fillcan
#include "fillcan/computing/compute_pipeline_builder.hpp"
#include "fillcan/shader/pipeline_builder.hpp"
#include <cstring>
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/drawing/framebuffer.hpp>
#include <fillcan/drawing/render_pass.hpp>
#include <fillcan/drawing/render_pass_builder.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/buffer_view.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_builder.hpp>
#include <fillcan/memory/image_director.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/memory/memory.hpp>
#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_pool_builder.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/descriptor_set_layout_builder.hpp>
#include <fillcan/shader/shader_module.hpp>
#include <fillcan/swapchain/swapchain.hpp>
#include "fillcan/computing/compute_pipeline.hpp"
#include "fillcan/shader/pipeline.hpp"
#include "fillcan/shader/pipeline_layout.hpp"

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

        fillcan::CommandRecording graphicsRecording2 = currentDevice->getGraphicsQueue()->createRecording(1, 1);
        fillcan::CommandRecording computRecording = currentDevice->getComputeQueue()->createRecording(2, 1);

        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> descriptorSetLayouts = {};

        fillcan::DescriptorSetLayoutBuilder descriptorSetLayoutBuilder{};
        descriptorSetLayoutBuilder.setLogicalDevice(currentDevice);
        descriptorSetLayoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);
        descriptorSetLayoutBuilder.addBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1, VK_SHADER_STAGE_COMPUTE_BIT);
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

        std::vector<char> code = {'t', 'e', 's', 't'};
        fillcan::ShaderModule shaderModule =
            fillcan::ShaderModule(currentDevice, code, std::move(descriptorSetLayouts), std::move(descriptorPoolBuilder.getResult()));

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

        fillcan::Swapchain* pSwapchain = upFillcan->createSwapchain();
        std::cout << pSwapchain->getSwapchainHandle() << "\n";

        std::vector<fillcan::DescriptorSet*> pDescriptorSets = shaderModule.getDescriptorPool()->getDescriptorSets();

        /**
            Renderpass
        */
        fillcan::RenderPassBuilder renderPassBuilder = fillcan::RenderPassBuilder();
        renderPassBuilder.setLogicalDevice(currentDevice);
        VkAttachmentDescription colorAttachmentDescription1 = {.flags = 0,
                                                               .format = pSwapchain->getSurfaceFormat().format,
                                                               .samples = VK_SAMPLE_COUNT_1_BIT,
                                                               .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                                                               .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                                                               .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                                               .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                                                               .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                                                               .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR};
        renderPassBuilder.addColorAttachment(colorAttachmentDescription1, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
        renderPassBuilder.constructSubpass();
        std::unique_ptr<fillcan::RenderPass> renderPass = renderPassBuilder.getResult();

        std::cout << "Renderpass: " << renderPass->getRenderPassHandle() << "\n";
        /* */

        fillcan::CommandRecording presentRecording = currentDevice->getPresentQueue()->createRecording(2, 1);
        fillcan::CommandBuffer* pSwapchainCommandBuffer = presentRecording.pPrimaryCommandBuffers[0];
        pSwapchainCommandBuffer->begin();
        fillcan::SwapchainImage swapchainImage1 = pSwapchain->getNextImage(pSwapchainCommandBuffer);
        pSwapchainCommandBuffer->end();
        std::cout << (swapchainImage1.outOfDate ? "Out of Date " : " ") << swapchainImage1.index << "\n";

        std::vector<fillcan::ImageView*> pAttachments = {
            swapchainImage1.image.createImageView(VK_IMAGE_VIEW_TYPE_2D, pSwapchain->getSurfaceFormat().format)};
        fillcan::Framebuffer framebuffer1 =
            fillcan::Framebuffer(currentDevice, renderPass.get(), pAttachments, pSwapchain->getExtent().width, pSwapchain->getExtent().height, 1);
        std::cout << "Framebuffer: " << framebuffer1.getFramebufferHandle() << "\n";

        fillcan::CommandRecording graphicsRecording = currentDevice->getGraphicsQueue()->createRecording(1, 0);

        std::vector<VkClearValue> clearValues = {};
        clearValues.reserve(1);
        clearValues.emplace_back((VkClearValue){.color = (VkClearColorValue){.float32 = {0.0f, 0.0f, 0.0f, 1.0f}}});
        graphicsRecording.pPrimaryCommandBuffers[0]->begin();
        renderPass->begin(graphicsRecording.pPrimaryCommandBuffers[0], &framebuffer1, &clearValues);

        /*
            Compute Pipeline
        */
        fillcan::ComputePipelineBuilder computePipelineBuilder = fillcan::ComputePipelineBuilder();
        computePipelineBuilder.setLogicalDevice(currentDevice);
        computePipelineBuilder.setFlags(0);
        computePipelineBuilder.setShaderStage(
            fillcan::PipelineShaderStage{.stage = VK_SHADER_STAGE_COMPUTE_BIT, .pShaderModule = &shaderModule, .name = "main"});
        fillcan::ComputePipeline computePipeline = computePipelineBuilder.getResult();
        std::cout << computePipeline.getPipelineLayout()->getDescriptorSetLayouts().size() << "\n";
        /* */

        upFillcan->MainLoop(std::bind(&App::update, this));
    }

    void App::update() {}
} // namespace app