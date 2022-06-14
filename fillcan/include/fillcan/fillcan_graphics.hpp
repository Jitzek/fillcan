#pragma once

// vulkan
#include "fillcan/graphics/render_pass_builder.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/fillcan.hpp>
#include <fillcan/graphics/framebuffer.hpp>
#include <fillcan/graphics/render_pass.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class FillcanGraphics : public Fillcan {
      private:
        std::vector<std::unique_ptr<Swapchain>> upSwapchains = {};
        std::vector<std::unique_ptr<RenderPass>> upRenderPasses = {};

      public:
        FillcanGraphics(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                        VkPhysicalDeviceFeatures requiredDeviceFeatures = {});
        ~FillcanGraphics();

        unsigned int createSwapchain(BufferMode bufferMode = FILLCAN_BUFFERING_TRIPLE, VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR);
        unsigned int recreateSwapchain(BufferMode bufferMode = FILLCAN_BUFFERING_TRIPLE, VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, unsigned int index = 0);
        Swapchain* getSwapchain(unsigned int index = 0);
        std::vector<Swapchain*> getSwapchains();
        void destroySwapchain(unsigned int index = 0);

        unsigned int createRenderPass(RenderPassBuilder& builder);
        RenderPass* getRenderPass(unsigned int index = 0);
        std::vector<RenderPass*> getRenderPasses();
        void destroyRenderPass(unsigned int index = 0);
    };
} // namespace fillcan