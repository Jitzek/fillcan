// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/drawing/framebuffer.hpp>
#include <fillcan/drawing/render_pass.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image_view.hpp>

// std
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Framebuffer::Framebuffer(LogicalDevice* pLogicalDevice, RenderPass* pRenderPass, std::vector<ImageView*> pAttachments, unsigned int width,
                             unsigned int height, unsigned int layers)
        : pLogicalDevice(pLogicalDevice), pAttachments(pAttachments), extent((VkExtent2D){.width = width, .height = height}), layers(layers) {
        VkFramebufferCreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferCreateInfo.pNext = nullptr;
        framebufferCreateInfo.flags = 0;
        framebufferCreateInfo.renderPass = pRenderPass->getRenderPassHandle();

        std::vector<VkImageView> hImageViews = {};
        hImageViews.reserve(pAttachments.size());
        std::vector<ImageView*> pImageViews = {};
        std::transform(this->pAttachments.begin(), this->pAttachments.end(), std::back_inserter(hImageViews),
                       [](ImageView* pImageView) { return pImageView->getImageViewHandle(); });
        framebufferCreateInfo.attachmentCount = static_cast<uint32_t>(hImageViews.size());
        framebufferCreateInfo.pAttachments = hImageViews.data();

        framebufferCreateInfo.width = this->extent.width;
        framebufferCreateInfo.height = this->extent.height;
        framebufferCreateInfo.layers = this->layers;

        if (vkCreateFramebuffer(this->pLogicalDevice->getLogicalDeviceHandle(), &framebufferCreateInfo, nullptr, &this->hFramebuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create framebuffer");
        }
    }
    Framebuffer::~Framebuffer() { vkDestroyFramebuffer(this->pLogicalDevice->getLogicalDeviceHandle(), this->hFramebuffer, nullptr); }

    VkFramebuffer Framebuffer::getFramebufferHandle() { return this->hFramebuffer; }
    VkExtent2D Framebuffer::getExtent() { return this->extent; }
} // namespace fillcan