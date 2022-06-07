#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>
#include <vector>

namespace fillcan {
    class RenderPass;
    class LogicalDevice;
    class RenderPassBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        std::vector<VkAttachmentDescription> attachments = {};
        std::vector<VkAttachmentReference> inputAttachmentReferences = {};
        std::vector<VkAttachmentReference> colorAttachmentReferences = {};
        std::vector<VkAttachmentReference> resolveAttachmentReferences = {};
        VkAttachmentReference depthStencilAttachmentReference = (VkAttachmentReference){.attachment = VK_ATTACHMENT_UNUSED};
        std::vector<uint32_t> preserveAttachmentReferences = {};
        bool resolve = false;

        std::vector<VkSubpassDescription> subpasses = {};

        std::vector<VkSubpassDependency> dependencies = {};
        unsigned int srcSubpass = -1;
        unsigned int dstSubpass = -1;
        VkPipelineStageFlags srcStageMask = 0;
        VkPipelineStageFlags dstStageMask = 0;
        VkAccessFlags srcAccessMask = 0;
        VkAccessFlags dstAccessMask = 0;

        void addAttachment(VkAttachmentDescription& attachment, bool preserve);

      public:
        RenderPassBuilder();
        ~RenderPassBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void addInputAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve = false);
        void addColorAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve = false, bool resolve = false);
        void addResolveAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve = false);
        void setDepthStencilAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve = false);
        void addSubpass();

        void setSubpassSrcDependency(VkPipelineStageFlags srcStageMask, VkAccessFlags srcAccessMask);
        void setSubpassDstDependency(VkPipelineStageFlags dstStageMask, VkAccessFlags dstAccessMask);
        void addSubpassDependency(VkDependencyFlags dependencyFlags);

        void reset();
        std::unique_ptr<RenderPass> getResult();
    };
} // namespace fillcan