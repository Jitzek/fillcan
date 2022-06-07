#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class RenderPass {
      private:
        VkRenderPass hRenderPass;
        LogicalDevice* pLogicalDevice;
        std::vector<VkAttachmentDescription> attachments;
        // std::vector<VkAttachmentReference> inputAttachmentReferences;
        // std::vector<VkAttachmentReference> colorAttachmentReferences;
        // std::vector<VkAttachmentReference> resolveAttachmentReferences;
        // std::vector<VkAttachmentReference> depthStencilAttachmentReferences;
        // std::vector<uint32_t> preserveAttachmentReferences;
        std::vector<VkSubpassDescription> subpasses;
        std::vector<VkSubpassDependency> dependencies;

      public:
        RenderPass(LogicalDevice* pLogicalDevice, std::vector<VkAttachmentDescription> attachments, std::vector<VkSubpassDescription> subpasses,
                   std::vector<VkSubpassDependency> dependencies);
        ~RenderPass();

        VkRenderPass getRenderPassHandle();
    };
} // namespace fillcan