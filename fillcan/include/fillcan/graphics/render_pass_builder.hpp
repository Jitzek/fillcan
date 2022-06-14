#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <cstdint>
#include <memory>
#include <vector>
namespace fillcan {
    class RenderPass;
    class LogicalDevice;
    class RenderPassBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;

        std::vector<VkAttachmentDescription> attachmentDescriptions = {};

        std::vector<VkAttachmentReference> inputAttachments = {};
        std::vector<VkAttachmentReference> colorAttachments = {};
        std::unique_ptr<VkAttachmentReference> upDepthStencilAttachment = nullptr;
        std::vector<uint32_t> preserveAttachments = {};
        bool resolveCurrentBatch = false;

        std::vector<VkSubpassDescription> subpassDescriptions = {};
        std::vector<VkSubpassDependency> dependencyDescriptions = {};

      public:
        RenderPassBuilder();
        ~RenderPassBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        unsigned int addAttachment(VkAttachmentDescription attachmentDescription);

        void addInputAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);
        void addColorAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);
        void setDepthStencilAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);
        void resolveCurrentAttachments();

        unsigned int constructSubpass();

        void addDependency(VkSubpassDependency dependencyDescription);

        void reset();
        std::unique_ptr<RenderPass> getResult();
    };
} // namespace fillcan