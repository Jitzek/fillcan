
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

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    void App::run() {
        std::string name = "Graphics Pipeline Test Application";
        std::cout << "Running App \"" << name << "\"\n";

        /*
            Instance Fillcan
        */
        upFillcan = std::make_unique<fillcan::FillcanGraphics>(name.c_str(), 1.0, 800, 600, (VkPhysicalDeviceFeatures){.samplerAnisotropy = true});

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
            Create a renderpass
        */
        // this->upRenderPass = this->createRenderPass();
        /* */

        /*
            Create a framebuffer
        */
        // fillcan::Framebuffer framebuffer = fillcan::Framebuffer(this->upFillcan->getCurrentDevice(), upRenderPass.get(), );
        /* */

        // std::unique_ptr<fillcan::GraphicsPipeline> upGraphicsPipeline = this->createGraphicsPipeline();

        /** TODO: PUT IN UPDATE **/

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
        /* */

        /*
            Prepare vertices to draw
        */
        const std::vector<Vertex> vertices = {
            {{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}};
        /* */

        /*
            Prepare indices of vertices
        */
        const std::vector<uint16_t> indices = {0, 1, 2};
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
        void** ppVertexData = this->upVertexBuffer->getMemory()->map();
        void** ppIndexData = this->upIndexBuffer->getMemory()->map();
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

        this->upSemaphores.resize(this->upFillcan->getSwapchain()->getImageCount());
        this->upFrameFences.resize(this->upFillcan->getSwapchain()->getImageCount());

        for (size_t i = 0; i < this->upFillcan->getSwapchain()->getImageCount(); i++) {
            this->pCommandRecordings.push_back(this->upFillcan->getCurrentDevice()->getGraphicsQueue()->createRecording(1, 0));
            this->upFrameFences[i] =
                std::move(std::make_unique<fillcan::Fence>(this->upFillcan->getCurrentDevice(), VK_FENCE_CREATE_SIGNALED_BIT));
        }

        this->upFramebuffers.resize(this->upFillcan->getSwapchain()->getImageCount());

        /**
            UPDATE
        **/

        int i = 0;
        while (!this->upFillcan->getWindow()->shouldClose()) {
            this->upFillcan->pollEvents();
            this->update();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "Done: " << i;

        // upFillcan->MainLoop(std::bind(&App::update, this, std::placeholders::_1));
    }

    void App::update(/*std::chrono::duration<double> deltaTime*/) {
        fillcan::SwapchainImage swapchainImage = this->upFillcan->getSwapchain()->getNextImage();
        this->upFrameFences[currentFrame]->reset();

        // Check if swapchain image is valid
        if (swapchainImage.outOfDate || this->upFillcan->getWindow()->wasResized()) {
            this->upFillcan->recreateSwapchain(2, VK_PRESENT_MODE_FIFO_KHR);
            // swapchainImage = this->upFillcan->getSwapchain()->getNextImage();
            return;
        }

        fillcan::CommandRecording* pGraphicsCommandRecording = this->pCommandRecordings[this->currentFrame];
        fillcan::CommandBuffer* pGraphicsCommandBuffer = pGraphicsCommandRecording->pPrimaryCommandBuffers[0];
        pGraphicsCommandRecording->resetAll();
        pGraphicsCommandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        // Define semaphore for when image is ready
        pGraphicsCommandRecording->pWaitSemaphores.push_back(swapchainImage.pSemaphore);
        pGraphicsCommandRecording->waitDstStageMask = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        this->upSemaphores[this->currentFrame] = std::move(std::make_unique<fillcan::Semaphore>(this->upFillcan->getCurrentDevice()));
        pGraphicsCommandRecording->pSignalSemaphores.push_back(this->upSemaphores[this->currentFrame].get());

        // Create imageviews which will be used as attachments
        std::vector<fillcan::ImageView*> pAttachments = {};
        pAttachments.reserve(1);
        pAttachments.push_back(swapchainImage.pImage->createImageView(
            VK_IMAGE_VIEW_TYPE_2D, this->upFillcan->getSwapchain()->getSurfaceFormat().format,
            (VkImageSubresourceRange){
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1}));
        /* */

        /*
            Create framebuffer
        */
        this->upFramebuffers[this->currentFrame] = std::move(std::make_unique<fillcan::Framebuffer>(
            this->upFillcan->getCurrentDevice(), this->upFillcan->getRenderPass(), pAttachments,
            this->upFillcan->getSwapchain()->getImageExtent().width, this->upFillcan->getSwapchain()->getImageExtent().height,
            this->upFillcan->getSwapchain()->getImageArrayLayers()));
        /* */

        std::vector<VkClearValue> clearValues = {(VkClearValue){.color = (VkClearColorValue){.float32 = {0.0f, 0.0f, 0.0f, 1.0f}}}};
        this->upFillcan->getRenderPass()->begin(pGraphicsCommandBuffer, this->upFramebuffers[this->currentFrame].get(), &clearValues);

        upGraphicsPipeline->bindToCommandBuffer(pGraphicsCommandBuffer);
        upGraphicsPipeline->start();
        VkViewport viewport = (VkViewport){.x = 0.0f,
                                           .y = 0.0f,
                                           .width = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().width),
                                           .height = static_cast<float>(this->upFillcan->getSwapchain()->getImageExtent().height),
                                           .minDepth = 0.0f,
                                           .maxDepth = 1.0f};
        VkRect2D scissor = (VkRect2D){.offset = {0, 0}, .extent = this->upFillcan->getSwapchain()->getImageExtent()};
        vkCmdSetViewport(pGraphicsCommandBuffer->getCommandBufferHandle(), 0, 1, &viewport);
        vkCmdSetScissor(pGraphicsCommandBuffer->getCommandBufferHandle(), 0, 1, &scissor);

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

        // upGraphicsPipeline->draw(3);
        upGraphicsPipeline->drawIndexed(3);

        this->upFillcan->getRenderPass()->end();

        // this->upFrameFence->reset();
        pGraphicsCommandRecording->endAll();
        pGraphicsCommandRecording->submitAll(this->upFrameFences[currentFrame].get());
        // this->upFrameFence->waitFor();

        this->upFillcan->getSwapchain()->present(&swapchainImage, {this->upSemaphores[currentFrame]->getSemaphoreHandle()});
        // pGraphicsCommandRecording->free();

        this->upFrameFences[currentFrame]->waitFor();
        this->currentFrame = (currentFrame + 1) % this->upFillcan->getSwapchain()->getImageCount();
    }

    void App::createRenderPass() {
        fillcan::RenderPassBuilder renderPassBuilder = {};
        renderPassBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        unsigned int swapChainAttachmentIndex =
            renderPassBuilder.addAttachment((VkAttachmentDescription){.flags = 0,
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
        renderPassBuilder.addDependency((VkSubpassDependency){.srcSubpass = VK_SUBPASS_EXTERNAL,
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
        graphicsPipelineBuilder.addShaderStage(
            (fillcan::PipelineShaderStage){.stage = VK_SHADER_STAGE_VERTEX_BIT, .pShaderModule = pVertexShaderModule, .name = "main"});
        graphicsPipelineBuilder.addShaderStage(
            (fillcan::PipelineShaderStage){.stage = VK_SHADER_STAGE_FRAGMENT_BIT, .pShaderModule = pFragmentShaderModule, .name = "main"});
        graphicsPipelineBuilder.setInputAssemblyState({VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE});

        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions = {};
        vertexInputBindingDescriptions.reserve(1);
        vertexInputBindingDescriptions.push_back(
            (VkVertexInputBindingDescription){.binding = 0, .stride = sizeof(Vertex), .inputRate = VK_VERTEX_INPUT_RATE_VERTEX});

        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions = {};
        vertexInputAttributeDescriptions.reserve(2);
        vertexInputAttributeDescriptions.push_back((VkVertexInputAttributeDescription){
            .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, position)});
        vertexInputAttributeDescriptions.push_back((VkVertexInputAttributeDescription){
            .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, color)});
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

        graphicsPipelineBuilder.setMultisampleState((fillcan::PipelineMultisampleState){.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
                                                                                        .sampleShadingEnable = VK_FALSE,
                                                                                        .minSampleShading = 1.0f,
                                                                                        .sampleMask = {},
                                                                                        .alphaToCoverageEnable = VK_FALSE,
                                                                                        .alphaToOneEnable = VK_FALSE});

        std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments = {};
        colorBlendAttachments.push_back((VkPipelineColorBlendAttachmentState){.blendEnable = VK_FALSE,
                                                                              .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
                                                                              .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
                                                                              .colorBlendOp = VK_BLEND_OP_ADD,
                                                                              .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                                                                              .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                                                                              .alphaBlendOp = VK_BLEND_OP_ADD,
                                                                              .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                                                                VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT});
        graphicsPipelineBuilder.setColorBlendState({VK_FALSE, VK_LOGIC_OP_COPY, colorBlendAttachments, std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}});

        std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
        graphicsPipelineBuilder.setDynamicState((fillcan::PipelineDynamicState){.dynamicStates = dynamicStates});

        graphicsPipelineBuilder.setRenderPass(this->upFillcan->getRenderPass());

        this->upGraphicsPipeline = graphicsPipelineBuilder.getResult();
    }
} // namespace app_graphics_pipeline_test