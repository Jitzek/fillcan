
// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/graphics/render_pass_builder.hpp>

// std
#include <memory>
#include <utility>

namespace fillcan {
    RenderPassBuilder::RenderPassBuilder() {}
    RenderPassBuilder::~RenderPassBuilder() {}

    void RenderPassBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    unsigned int RenderPassBuilder::addAttachment(VkAttachmentDescription description) {
        this->attachmentDescriptions.push_back(description);
        return this->attachmentDescriptions.size() - 1;
    }

    void RenderPassBuilder::addInputAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve) {
        VkAttachmentReference attachmentReference = {};
        attachmentReference.attachment = attachmentDescriptionIndex;
        attachmentReference.layout = layout;
        this->inputAttachments.push_back(attachmentReference);
        if (preserve) {
            this->preserveAttachments.push_back(attachmentDescriptionIndex);
        }
    }

    void RenderPassBuilder::addColorAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve) {
        VkAttachmentReference attachmentReference = {};
        attachmentReference.attachment = attachmentDescriptionIndex;
        attachmentReference.layout = layout;
        this->colorAttachments.push_back(attachmentReference);
        if (preserve) {
            this->preserveAttachments.push_back(attachmentDescriptionIndex);
        }
    }

    void RenderPassBuilder::setDepthStencilAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve) {
        VkAttachmentReference attachmentReference = {};
        attachmentReference.attachment = attachmentDescriptionIndex;
        attachmentReference.layout = layout;
        this->upDepthStencilAttachment = std::make_unique<VkAttachmentReference>(attachmentReference);
        if (preserve) {
            this->preserveAttachments.push_back(attachmentDescriptionIndex);
        }
    }

    void RenderPassBuilder::resolveCurrentAttachments() { this->resolveCurrentBatch = true; }

    unsigned int RenderPassBuilder::constructSubpass() {
        VkSubpassDescription subpassDescription = {};
        subpassDescription.flags = 0;
        subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDescription.inputAttachmentCount = static_cast<uint32_t>(this->inputAttachments.size());
        subpassDescription.pInputAttachments = this->inputAttachments.data();
        subpassDescription.colorAttachmentCount = static_cast<uint32_t>(this->colorAttachments.size());
        subpassDescription.pColorAttachments = this->colorAttachments.data();
        if (resolveCurrentBatch) {
            subpassDescription.pResolveAttachments = this->colorAttachments.data();
        }
        subpassDescription.pDepthStencilAttachment = this->upDepthStencilAttachment.get();
        subpassDescription.preserveAttachmentCount = static_cast<uint32_t>(this->preserveAttachments.size());
        subpassDescription.pPreserveAttachments = this->preserveAttachments.data();
        this->subpassDescriptions.push_back(subpassDescription);
        return this->subpassDescriptions.size() - 1;
    }

    void RenderPassBuilder::addDependency(VkSubpassDependency dependency) { this->dependencyDescriptions.push_back(dependency); }

    void RenderPassBuilder::reset() {
        this->pLogicalDevice = nullptr;

        this->attachmentDescriptions.clear();

        this->inputAttachments.clear();
        this->colorAttachments.clear();
        this->upDepthStencilAttachment = nullptr;
        this->preserveAttachments.clear();
        this->resolveCurrentBatch = false;

        this->subpassDescriptions.clear();
        this->dependencyDescriptions.clear();
    }

    std::unique_ptr<RenderPass> RenderPassBuilder::getResult() {
        return std::move(std::make_unique<RenderPass>(this->pLogicalDevice, this->attachmentDescriptions, this->subpassDescriptions,
                                                      this->dependencyDescriptions));
    }
} // namespace fillcan