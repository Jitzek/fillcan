// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/graphics/render_pass_builder.hpp>

// std
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace fillcan {
    RenderPassBuilder::RenderPassBuilder() {}
    RenderPassBuilder::~RenderPassBuilder() {}

    void RenderPassBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void RenderPassBuilder::addAttachment(VkAttachmentDescription& attachment, bool preserve) {
        this->attachments.push_back(attachment);
        if (preserve) {
            this->preserveAttachmentReferences.push_back(static_cast<uint32_t>(this->attachments.size() - 1));
        }
    }

    void RenderPassBuilder::addInputAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve) {
        this->addAttachment(attachment, preserve);
        this->inputAttachmentReferences.push_back(
            (VkAttachmentReference{.attachment = static_cast<uint32_t>(this->attachments.size() - 1), .layout = layout}));
    }

    void RenderPassBuilder::addColorAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve, bool resolve) {
        this->addAttachment(attachment, preserve);
        this->colorAttachmentReferences.push_back(
            (VkAttachmentReference{.attachment = static_cast<uint32_t>(this->attachments.size() - 1), .layout = layout}));
        this->resolveAttachmentReferences.push_back(
            (VkAttachmentReference{.attachment = static_cast<uint32_t>(this->attachments.size() - 1), .layout = layout}));
        if (resolve) {
            this->resolve = true;
        }
    }

    void RenderPassBuilder::setDepthStencilAttachment(VkAttachmentDescription attachment, VkImageLayout layout, bool preserve) {
        this->addAttachment(attachment, preserve);
        this->upDepthStencilAttachmentReference = std::make_unique<VkAttachmentReference>(
            (VkAttachmentReference{.attachment = static_cast<uint32_t>(this->attachments.size() - 1), .layout = layout}));
    }

    void RenderPassBuilder::constructSubpass() {
        VkSubpassDescription subpassDescription = {};
        subpassDescription.flags = 0;
        subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDescription.inputAttachmentCount = static_cast<uint32_t>(this->inputAttachmentReferences.size());
        subpassDescription.pInputAttachments = this->inputAttachmentReferences.data();
        subpassDescription.colorAttachmentCount = static_cast<uint32_t>(this->colorAttachmentReferences.size());
        subpassDescription.pColorAttachments = this->colorAttachmentReferences.data();
        if (this->resolve) {
            subpassDescription.pResolveAttachments = this->resolveAttachmentReferences.data();
        } else {
            subpassDescription.pResolveAttachments = nullptr;
        }
        if (this->upDepthStencilAttachmentReference != nullptr) {
            subpassDescription.pDepthStencilAttachment = this->upDepthStencilAttachmentReference.get();
        } else {
            subpassDescription.pDepthStencilAttachment = nullptr;
        }
        subpassDescription.preserveAttachmentCount = static_cast<uint32_t>(this->preserveAttachmentReferences.size());
        subpassDescription.pPreserveAttachments = this->preserveAttachmentReferences.data();

        this->subpasses.push_back(subpassDescription);

        // Reset attachment reference variables for next subpass
        this->inputAttachmentReferences.clear();
        this->colorAttachmentReferences.clear();
        this->resolveAttachmentReferences.clear();
        this->upDepthStencilAttachmentReference = nullptr;
        this->preserveAttachmentReferences.clear();
        this->resolve = false;
    }

    void RenderPassBuilder::addSubpassDependency(unsigned int srcSubpassIndex, unsigned int dstSubpassIndex, VkPipelineStageFlags srcStageMask,
                                                 VkPipelineStageFlags dstStageMask, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask) {
        this->srcSubpass = srcSubpassIndex;
        this->dstSubpass = dstSubpassIndex;
        this->srcStageMask = srcStageMask;
        this->dstStageMask = dstStageMask;
        this->srcAccessMask = srcAccessMask;
        this->dstAccessMask = dstAccessMask;
    }

    void RenderPassBuilder::setSubpassSrcDependency(VkPipelineStageFlags srcStageMask, VkAccessFlags srcAccessMask) {
        this->srcSubpass = this->subpasses.size() - 1;
        this->srcStageMask = srcStageMask;
        this->srcAccessMask = srcAccessMask;
    }

    void RenderPassBuilder::setSubpassDstDependency(VkPipelineStageFlags dstStageMask, VkAccessFlags dstAccessMask) {
        this->dstSubpass = this->subpasses.size() - 1;
        this->dstStageMask = dstStageMask;
        this->dstAccessMask = dstAccessMask;
    }

    void RenderPassBuilder::constructSubpassDependency(VkDependencyFlags dependencyFlags) {
        if (this->srcSubpass == -1) {
            throw std::runtime_error("Source subpass dependency not set");
        }
        if (this->dstSubpass == -1) {
            throw std::runtime_error("Destination subpass dependency not set");
        }
        VkSubpassDependency subpassDependency = {};
        subpassDependency.srcSubpass = this->srcSubpass;
        subpassDependency.dstSubpass = this->dstSubpass;
        subpassDependency.srcStageMask = this->srcStageMask;
        subpassDependency.dstStageMask = this->dstStageMask;
        subpassDependency.srcAccessMask = this->srcAccessMask;
        subpassDependency.dstAccessMask = this->dstAccessMask;
        subpassDependency.dependencyFlags = dependencyFlags;
        this->dependencies.push_back(subpassDependency);

        // Reset subpass dependency variables for next subpass dependency
        this->srcSubpass = -1;
        this->dstSubpass = -1;
        this->srcStageMask = 0;
        this->dstStageMask = 0;
        this->srcAccessMask = 0;
        this->dstAccessMask = 0;
    }

    void RenderPassBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->attachments = {};
        this->inputAttachmentReferences.clear();
        this->colorAttachmentReferences.clear();
        this->resolveAttachmentReferences.clear();
        this->upDepthStencilAttachmentReference = nullptr;
        this->preserveAttachmentReferences.clear();
        this->resolve = false;
        this->subpasses.clear();
        this->dependencies.clear();
        this->srcSubpass = -1;
        this->dstSubpass = -1;
        this->srcStageMask = 0;
        this->dstStageMask = 0;
        this->srcAccessMask = 0;
        this->dstAccessMask = 0;
    }

    std::unique_ptr<RenderPass> RenderPassBuilder::getResult() {
        return std::move(std::make_unique<RenderPass>(this->pLogicalDevice, this->attachments, this->subpasses, this->dependencies));
    }
} // namespace fillcan