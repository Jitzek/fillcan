#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class RenderPass;
    class ImageView;
    class Framebuffer {
      private:
        VkFramebuffer hFramebuffer;
        LogicalDevice* pLogicalDevice;
        std::vector<ImageView*> pAttachments;
        VkExtent2D extent;
        unsigned int layers;

      public:
        Framebuffer(LogicalDevice* pLogicalDevice, RenderPass* pRenderPass, std::vector<ImageView*> pAttachments, unsigned int width,
                    unsigned int height, unsigned int layers);
        ~Framebuffer();

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        VkFramebuffer getFramebufferHandle();

        VkExtent2D getExtent();
    };
} // namespace fillcan