
#include "app.hpp"

// vulkan
#include "fillcan/memory/buffer.hpp"
#include "fillcan/memory/memory.hpp"
#include "fillcan/shader/descriptor_pool_builder.hpp"
#include "fillcan/shader/shader_module.hpp"
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
#include "fillcan/memory/buffer_director.hpp"
#include "fillcan/memory/image_view.hpp"
#include <cstddef>
#include <cstring>
#include <fillcan/graphics/graphics_pipeline_builder.hpp>

// std
#include <memory>
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
        this->upFillcan->createSwapchain(fillcan::FILLCAN_BUFFERING_TRIPLE, VK_PRESENT_MODE_FIFO_KHR);
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
            Create and begin commandbuffer(s)
        */
        fillcan::CommandRecording* pGraphicsCommandRecording = this->upFillcan->getCurrentDevice()->getGraphicsQueue()->createRecording(1, 0);
        fillcan::CommandBuffer* pGraphicsCommandBuffer = pGraphicsCommandRecording->pPrimaryCommandBuffers[0];
        pGraphicsCommandBuffer->begin();
        /* */

        /*
            Create attachments
        */
        // Create Image Views of the swapchain images
        fillcan::SwapchainImage swapchainImage = this->upFillcan->getSwapchain()->getNextImage(pGraphicsCommandBuffer);

        // Check if swapchain image is valid
        if (swapchainImage.outOfDate) {
            this->upFillcan->recreateSwapchain(fillcan::FILLCAN_BUFFERING_TRIPLE, VK_PRESENT_MODE_FIFO_KHR);
            swapchainImage = this->upFillcan->getSwapchain()->getNextImage(pGraphicsCommandBuffer);
        }

        // Create imageviews which will be used as attachments
        std::vector<fillcan::ImageView*> pAttachments = {};
        pAttachments.reserve(1);
        pAttachments.push_back(swapchainImage.upImage->createImageView(
            VK_IMAGE_VIEW_TYPE_2D, this->upFillcan->getSwapchain()->getSurfaceFormat().format,
            (VkImageSubresourceRange){
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1}));
        /* */

        /*
            Create Render Pass
        */
        this->createRenderPass();
        /* */

        /**
            UPDATE
        **/

        /*
            Create framebuffer
        */
        this->upFillcan->getRenderPass()->createFramebuffer(pAttachments, this->upFillcan->getSwapchain()->getImageExtent().width,
                                                            this->upFillcan->getSwapchain()->getImageExtent().height,
                                                            this->upFillcan->getSwapchain()->getImageArrayLayers());
        // fillcan::Framebuffer* pFramebuffer = this->upFillcan->getRenderPass()->getFramebuffer();
        fillcan::Framebuffer framebuffer =
            fillcan::Framebuffer(this->upFillcan->getCurrentDevice(), this->upFillcan->getRenderPass(), pAttachments,
                                 this->upFillcan->getSwapchain()->getImageExtent().width, this->upFillcan->getSwapchain()->getImageExtent().height,
                                 this->upFillcan->getSwapchain()->getImageArrayLayers());
        /* */

        /*
            Create shader modules
        */
        std::unique_ptr<fillcan::ShaderModule> vertexShaderModule = this->upFillcan->createShaderModule(
            "./apps/graphics_pipeline_test/shaders", "simple.vert", shaderc_vertex_shader, {}, nullptr, true, true);
        /* */

        /*
            Create Graphics Pipeline
        */
        fillcan::GraphicsPipelineBuilder graphicsPipelineBuilder{};
        graphicsPipelineBuilder.setLogicalDevice(this->upFillcan->getCurrentDevice());
        graphicsPipelineBuilder.addShaderStage(
            (fillcan::PipelineShaderStage){.stage = VK_SHADER_STAGE_VERTEX_BIT, .pShaderModule = vertexShaderModule.get(), .name = "main"});

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

        graphicsPipelineBuilder.setInputAssemblyState(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE);
        graphicsPipelineBuilder.setVertexInputState(vertexInputBindingDescriptions, vertexInputAttributeDescriptions);
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
        std::unique_ptr<fillcan::Buffer> upVertexBuffer =
            bufferDirector.makeVertexBuffer(this->upFillcan->getCurrentDevice(), sizeof(vertices[0]) * vertices.size());
        /* */

        /*
            Create indexbuffer
        */
        std::unique_ptr<fillcan::Buffer> upIndexBuffer =
            bufferDirector.makeIndexBuffer(this->upFillcan->getCurrentDevice(), sizeof(indices[0]) * indices.size());
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
        void** ppVertexData = vertexBufferMemory.map();
        void** ppIndexData = indexBufferMemory.map();
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
        vertexBufferMemory.unmap();
        indexBufferMemory.unmap();
        /* */

        /*
            Bind the vertex buffer
        */

        /* */

        swapchainImage.upImage->createImageView(
            VK_IMAGE_VIEW_TYPE_2D, this->upFillcan->getSwapchain()->getSurfaceFormat().format,
            (VkImageSubresourceRange){
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1});

        upFillcan->MainLoop(std::bind(&App::update, this));
    }

    void App::update() {}

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
        renderPassBuilder.constructSubpass();
        this->upFillcan->createRenderPass(renderPassBuilder);
    }

    // std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> App::createDescriptorSetLayouts() {}

    // std::unique_ptr<fillcan::DescriptorPool>

    // std::unique_ptr<fillcan::GraphicsPipeline> App::createGraphicsPipeline() {
    //     fillcan::GraphicsPipelineBuilder graphicsPipelineBuilder = fillcan::GraphicsPipelineBuilder();
    // }
} // namespace app_graphics_pipeline_test