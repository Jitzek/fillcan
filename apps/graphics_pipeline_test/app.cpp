
#include "app.hpp"
#include "fillcan/commands/command_buffer.hpp"
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/framebuffer.hpp"
#include "fillcan/graphics/graphics_pipeline.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/graphics/render_pass_builder.hpp"
#include "fillcan/graphics/swapchain.hpp"
#include "fillcan/memory/image_view.hpp"
#include "vulkan/vulkan_core.h"

// vulkan

// fillcan
#include <fillcan/graphics/graphics_pipeline_builder.hpp>
#include <memory>
#include <utility>
#include <vector>

// std

namespace app_graphics_pipeline_test {
    App::App() {}
    App::~App() {}

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

        /*
            Create framebuffer
        */
        this->upFillcan->getRenderPass()->createFramebuffer(pAttachments, this->upFillcan->getSwapchain()->getImageExtent().width,
                                                            this->upFillcan->getSwapchain()->getImageExtent().height,
                                                            this->upFillcan->getSwapchain()->getImageArrayLayers());
        fillcan::Framebuffer* pFramebuffer = this->upFillcan->getRenderPass()->getFramebuffer();
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
    // App::createDescriptorPool(std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>>& upDescriptorSetLayouts) {}

    // std::unique_ptr<fillcan::GraphicsPipeline> App::createGraphicsPipeline() {
    //     fillcan::GraphicsPipelineBuilder graphicsPipelineBuilder = fillcan::GraphicsPipelineBuilder();
    // }
} // namespace app_graphics_pipeline_test