
#include "app.hpp"

// vulkan
#include "shaderc/shaderc.h"
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/commands/command_buffer.hpp"
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/framebuffer.hpp"
#include "fillcan/graphics/graphics_pipeline.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/graphics/render_pass_builder.hpp"
#include "fillcan/graphics/swapchain.hpp"
#include "fillcan/memory/buffer.hpp"
#include "fillcan/memory/buffer_director.hpp"
#include "fillcan/memory/fence.hpp"
#include "fillcan/memory/image_view.hpp"
#include "fillcan/memory/memory.hpp"
#include "fillcan/memory/semaphore.hpp"
#include "fillcan/shader/descriptor_pool.hpp"
#include "fillcan/shader/descriptor_pool_builder.hpp"
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "fillcan/shader/shader_module.hpp"
#include <exception>
#include <fillcan/graphics/graphics_pipeline_builder.hpp>
#include <fillcan/shader/pipeline.hpp>

// std
#include <array>
#include <chrono>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

// glm
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>

namespace app_graphics_pipeline_test {
    App::App() {}
    App::~App() {}

    void App::run() {
        std::string name = "Graphics Pipeline Test Application";
        std::cout << "Running App \"" << name << "\"\n";

        /*
            Instance Fillcan
        */
        VkPhysicalDeviceFeatures requiredDeviceFeatures = {.samplerAnisotropy = true};
        upFillcan = std::make_unique<fillcan::FillcanGraphics>(name.c_str(), 1.0, 800, 600, requiredDeviceFeatures);

        // Select any device
        upFillcan->selectDevice(0);

        std::cout << "Using Device: " << upFillcan->getCurrentDevice()->getPhysicalDevice()->getProperties().deviceName << "\n";
        /* */

        /*
            Create a swapchain
        */
        this->upFillcan->createSwapchain(2, VK_PRESENT_MODE_FIFO_KHR);
        /* */

        /*
            Create Render Pass
        */
        this->createRenderPass();
        /* */

        /*
            Create shader modules
        */
        std::unique_ptr<fillcan::ShaderModule> upVertexShaderModule = this->upFillcan->createShaderModule(
            "./apps/graphics_pipeline_test/shaders", "simple.vert", shaderc_vertex_shader, {}, nullptr, true, false);
        std::unique_ptr<fillcan::ShaderModule> upFragmentShaderModule = this->upFillcan->createShaderModule(
            "./apps/graphics_pipeline_test/shaders", "simple.frag", shaderc_fragment_shader, {}, nullptr, true, false);
        /* */

        /*
            Create Graphics Pipeline
        */
        this->createGraphicsPipeline(upVertexShaderModule.get(), upFragmentShaderModule.get());
        if (this->upGraphicsPipeline->getDescriptorSets().size() > 0) {
            this->upGraphicsPipeline->bindDescriptorSets();
        }
        /* */

        /*
            Create vertexbuffer
        */
        fillcan::BufferDirector bufferDirector{};
        this->upVertexBuffer = bufferDirector.makeVertexBuffer(this->upFillcan->getCurrentDevice(), sizeof(vertices[0]) * vertices.size());
        /* */

        /*
            Create indexbuffer
        */
        this->upIndexBuffer = bufferDirector.makeIndexBuffer(this->upFillcan->getCurrentDevice(), sizeof(indices[0]) * indices.size());
        /* */

        /*
            Bind memory to resources
        */
        fillcan::Memory vertexBufferMemory =
            fillcan::Memory(this->upFillcan->getCurrentDevice(), upVertexBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        fillcan::Memory indexBufferMemory =
            fillcan::Memory(this->upFillcan->getCurrentDevice(), upIndexBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

        upVertexBuffer->bindMemory(&vertexBufferMemory);
        upIndexBuffer->bindMemory(&indexBufferMemory);
        /* */

        /*
            Map memory
        */
        this->ppVertexData = this->upVertexBuffer->getMemory()->map();
        this->ppIndexData = this->upIndexBuffer->getMemory()->map();
        /* */

        /*
            Fill buffers with data
        */
        memcpy(*ppVertexData, vertices.data(), upVertexBuffer->getSize());
        memcpy(*ppIndexData, indices.data(), upIndexBuffer->getSize());
        /* */

        /*
            Unmap memory
        */
        this->upVertexBuffer->getMemory()->unmap();
        this->upIndexBuffer->getMemory()->unmap();
        /* */

        for (size_t i = 0; i < this->upFillcan->getSwapchain()->getImageCount(); i++) {
            this->pCommandRecordings.push_back(this->upFillcan->getCurrentDevice()->getGraphicsQueue()->createRecording(1, 0));
            this->pCommandRecordings[i]->createFence(this->upFillcan->getCurrentDevice(), VK_FENCE_CREATE_SIGNALED_BIT);
        }

        this->upFramebuffers.resize(this->upFillcan->getSwapchain()->getImageCount());

        upFillcan->MainLoop(std::bind(&App::update, this, std::placeholders::_1));
    }

    void App::update(double deltaTime) {
        // Recreate swapchain if window was resized
        if (this->upFillcan->getWindow()->wasResized()) {
            this->upFillcan->recreateSwapchain();
            return;
        }

        // Get current command recording
        fillcan::CommandRecording* pCurrentGraphicsCommandRecording = this->pCommandRecordings[this->currentFrameIndex];
        fillcan::CommandBuffer* pCurrentGraphicsCommandBuffer = pCurrentGraphicsCommandRecording->pPrimaryCommandBuffers[0];

        // Wait for the command recording to have finished
        pCurrentGraphicsCommandRecording->waitForFence();
        pCurrentGraphicsCommandRecording->reset();

        // Start new command recording
        pCurrentGraphicsCommandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        fillcan::SwapchainImage swapchainImage = this->upFillcan->getSwapchain()->getNextImage();

        if (swapchainImage.outOfDate) {
            return;
        }

        // Define semaphore for when image is ready to be rendered to
        pCurrentGraphicsCommandRecording->pWaitSemaphores.emplace_back(swapchainImage.pSemaphoreImageReady);
        // Define the stage(s) at where the semaphore should be waited for
        pCurrentGraphicsCommandRecording->waitDstStageMask = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

        // Define semphore for when image is ready to present
        pCurrentGraphicsCommandRecording->pSignalSemaphores.push_back(swapchainImage.pSemaphorePresentReady);

        // Create imageviews which will be used as attachments
        std::vector<fillcan::ImageView*> pAttachments = {};
        pAttachments.reserve(1);
        pAttachments.emplace_back(swapchainImage.pImage->createImageView(
            VK_IMAGE_VIEW_TYPE_2D, this->upFillcan->getSwapchain()->getSurfaceFormat().format,
            {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1}));
        /* */

        /*
            Create framebuffer
        */
        this->upFramebuffers.at(this->currentFrameIndex) = std::move(std::make_unique<fillcan::Framebuffer>(
            this->upFillcan->getCurrentDevice(), this->upFillcan->getRenderPass(), pAttachments,
            this->upFillcan->getSwapchain()->getImageExtent().width, this->upFillcan->getSwapchain()->getImageExtent().height,
            this->upFillcan->getSwapchain()->getImageArrayLayers()));
        /* */

        std::vector<VkClearValue> clearValues = {{.color = {.float32 = {0.0f, 0.0f, 0.0f, 1.0f}}}};
        this->upFillcan->getRenderPass()->begin(pCurrentGraphicsCommandBuffer, this->upFramebuffers[this->currentFrameIndex].get(), &clearValues);

        upGraphicsPipeline->bindToCommandBuffer(pCurrentGraphicsCommandBuffer);
        VkViewport viewport = {.x = 0.0f,
                               .y = 0.0f,
                               .width = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().width),
                               .height = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().height),
                               .minDepth = 0.0f,
                               .maxDepth = 1.0f};
        VkRect2D scissor = {.offset = {0, 0}, .extent = this->upFillcan->getSwapchain()->getImageExtent()};
        vkCmdSetViewport(pCurrentGraphicsCommandBuffer->getCommandBufferHandle(), 0, 1, &viewport);
        vkCmdSetScissor(pCurrentGraphicsCommandBuffer->getCommandBufferHandle(), 0, 1, &scissor);

        /*
            Bind the vertex buffer
        */
        std::vector<fillcan::Buffer*> pVertexBuffers = {upVertexBuffer.get()};
        this->upGraphicsPipeline->bindVertexBuffers(pVertexBuffers);
        /* */
        /*
            Bind the index buffer
        */
        this->upGraphicsPipeline->bindIndexBuffer(upIndexBuffer.get(), VK_INDEX_TYPE_UINT16);
        /* */

        // upGraphicsPipeline->draw(this->vertices.size());
        upGraphicsPipeline->drawIndexed(this->indices.size());

        this->upFillcan->getRenderPass()->end();

        pCurrentGraphicsCommandRecording->endAll();
        pCurrentGraphicsCommandRecording->submit();

        if (!this->upFillcan->getSwapchain()->present(&swapchainImage, {swapchainImage.pSemaphorePresentReady->getSemaphoreHandle()})) {
            return;
        }

        this->currentFrameIndex = (currentFrameIndex + 1) % this->upFillcan->getSwapchain()->getImageCount();
    }

    void App::createRenderPass() {
        fillcan::RenderPassBuilder renderPassBuilder = {};
        renderPassBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        unsigned int swapChainAttachmentIndex = renderPassBuilder.addAttachment({.flags = 0,
                                                                                 .format = this->upFillcan->getSwapchain()->getSurfaceFormat().format,
                                                                                 .samples = VK_SAMPLE_COUNT_1_BIT,
                                                                                 .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                                                                                 .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                                                                                 .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                                                                 .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                                                                                 .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                                                                                 .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR});
        renderPassBuilder.addColorAttachment(swapChainAttachmentIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, false);
        unsigned int subpassIndex = renderPassBuilder.constructSubpass();
        renderPassBuilder.addDependency({.srcSubpass = VK_SUBPASS_EXTERNAL,
                                         .dstSubpass = subpassIndex,
                                         .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                         .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                         .srcAccessMask = 0,
                                         .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT});
        this->upFillcan->createRenderPass(renderPassBuilder);
    }

    // std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> App::createDescriptorSetLayouts() {}

    // std::unique_ptr<fillcan::DescriptorPool>

    void App::createGraphicsPipeline(fillcan::ShaderModule* pVertexShaderModule, fillcan::ShaderModule* pFragmentShaderModule) {
        fillcan::GraphicsPipelineBuilder graphicsPipelineBuilder{};
        graphicsPipelineBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        graphicsPipelineBuilder.addShaderStage({.stage = VK_SHADER_STAGE_VERTEX_BIT, .pShaderModule = pVertexShaderModule, .name = "main"});
        graphicsPipelineBuilder.addShaderStage({.stage = VK_SHADER_STAGE_FRAGMENT_BIT, .pShaderModule = pFragmentShaderModule, .name = "main"});
        graphicsPipelineBuilder.setInputAssemblyState({VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE});

        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions = {};
        vertexInputBindingDescriptions.reserve(1);
        vertexInputBindingDescriptions.push_back({.binding = 0, .stride = sizeof(Vertex), .inputRate = VK_VERTEX_INPUT_RATE_VERTEX});

        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions = {};
        vertexInputAttributeDescriptions.reserve(2);
        vertexInputAttributeDescriptions.push_back(
            {.location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, position)});
        vertexInputAttributeDescriptions.push_back(
            {.location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, color)});
        graphicsPipelineBuilder.setVertexInputState({vertexInputBindingDescriptions, vertexInputAttributeDescriptions});

        std::vector<VkViewport> viewports = {};
        viewports.resize(1);
        // viewports.push_back((VkViewport){.x = 0.0f,
        //                                  .y = 0.0f,
        //                                  .width = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().width),
        //                                  .height = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().height),
        //                                  .minDepth = 0.0f,
        //                                  .maxDepth = 1.0f});
        std::vector<VkRect2D> scissors = {};
        scissors.resize(1);
        // scissors.push_back((VkRect2D){.offset = {0, 0}, .extent = this->upFillcan->getSwapchain()->getImageExtent()});
        graphicsPipelineBuilder.addViewportState({viewports, scissors});

        graphicsPipelineBuilder.setRasterizationState({});

        graphicsPipelineBuilder.setMultisampleState({.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
                                                     .sampleShadingEnable = VK_FALSE,
                                                     .minSampleShading = 1.0f,
                                                     .sampleMask = {},
                                                     .alphaToCoverageEnable = VK_FALSE,
                                                     .alphaToOneEnable = VK_FALSE});

        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments = {};
        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.blendEnable = VK_FALSE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        colorBlendAttachments.push_back(colorBlendAttachment);
        graphicsPipelineBuilder.setColorBlendState({VK_FALSE, VK_LOGIC_OP_COPY, colorBlendAttachments, std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}});

        std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
        graphicsPipelineBuilder.setDynamicState({.dynamicStates = dynamicStates});

        graphicsPipelineBuilder.setRenderPass(this->upFillcan->getRenderPass());

        this->upGraphicsPipeline = graphicsPipelineBuilder.getResult();
    }
} // namespace app_graphics_pipeline_test