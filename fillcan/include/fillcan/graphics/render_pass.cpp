// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <algorithm>
#include <fillcan/graphics/framebuffer.hpp>
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace fillcan {
    RenderPass::RenderPass(LogicalDevice* pLogicalDevice, std::vector<VkAttachmentDescription> attachments,
                           std::vector<VkSubpassDescription> subpasses, std::vector<VkSubpassDependency> dependencies)
        : pLogicalDevice(pLogicalDevice), attachments(attachments), subpasses(subpasses), dependencies(dependencies) {
        VkRenderPassCreateInfo renderPassCreateInfo = {};
        renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassCreateInfo.pNext = nullptr;
        renderPassCreateInfo.flags = 0;
        renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassCreateInfo.pAttachments = attachments.data();
        renderPassCreateInfo.subpassCount = static_cast<uint32_t>(subpasses.size());
        renderPassCreateInfo.pSubpasses = subpasses.data();
        renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
        renderPassCreateInfo.pDependencies = dependencies.data();
        if (vkCreateRenderPass(this->pLogicalDevice->getLogicalDeviceHandle(), &renderPassCreateInfo, nullptr, &this->hRenderPass) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create renderpass");
        }
    }

    RenderPass::~RenderPass() { vkDestroyRenderPass(this->pLogicalDevice->getLogicalDeviceHandle(), this->hRenderPass, nullptr); }

    VkRenderPass RenderPass::getRenderPassHandle() { return this->hRenderPass; }

    std::vector<VkAttachmentDescription>& RenderPass::getAttachments() { return this->attachments; }

    std::vector<VkSubpassDescription>& RenderPass::getSubpasses() { return this->subpasses; }

    std::vector<VkSubpassDependency>& RenderPass::getDependencies() { return this->dependencies; }

    void RenderPass::begin(CommandBuffer* pCommandBuffer, Framebuffer* pFramebuffer, std::vector<VkClearValue>* pClearValues, VkRect2D* pRenderArea) {
        this->pCommandBuffer = pCommandBuffer;
        VkRenderPassBeginInfo renderPassBeginInfo = {};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.pNext = nullptr;
        renderPassBeginInfo.renderPass = this->hRenderPass;
        renderPassBeginInfo.framebuffer = pFramebuffer->getFramebufferHandle();
        if (pRenderArea != nullptr) {
            renderPassBeginInfo.renderArea = *pRenderArea;
        } else {
            renderPassBeginInfo.renderArea = (VkRect2D){.offset = {0, 0}, .extent = pFramebuffer->getExtent()};
        }
        if (pClearValues != nullptr) {
            renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(pClearValues->size());
            renderPassBeginInfo.pClearValues = pClearValues->data();
        } else {
            renderPassBeginInfo.clearValueCount = 0;
            renderPassBeginInfo.pClearValues = nullptr;
        }
        vkCmdBeginRenderPass(this->pCommandBuffer->getCommandBufferHandle(), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void RenderPass::end() {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Attempting to end renderpass when it has not begun");
        }
        vkCmdEndRenderPass(this->pCommandBuffer->getCommandBufferHandle());
        this->pCommandBuffer = nullptr;
    }

    unsigned int RenderPass::createFramebuffer(std::vector<ImageView*> pAttachments, unsigned int width, unsigned int height, unsigned int layers) {
        this->upFramebuffers.push_back(
            std::move(std::make_unique<Framebuffer>(Framebuffer(this->pLogicalDevice, this, pAttachments, width, height, layers))));
        return this->upFramebuffers.size() - 1;
    }

    Framebuffer* RenderPass::getFramebuffer(unsigned int index) { return this->upFramebuffers[index].get(); }

    std::vector<Framebuffer*> RenderPass::getFramebuffers() {
        std::vector<Framebuffer*> pFramebuffers = {};
        pFramebuffers.reserve(this->upFramebuffers.size());
        std::transform(this->upFramebuffers.begin(), this->upFramebuffers.end(), std::back_inserter(pFramebuffers),
                       [](const std::unique_ptr<Framebuffer>& upFramebuffer) { return upFramebuffer.get(); });
        return pFramebuffers;
    }

    void RenderPass::destroyFramebuffer(unsigned int index) { this->upFramebuffers.erase(this->upFramebuffers.begin() + index); }
} // namespace fillcan