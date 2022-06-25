// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/framebuffer.hpp>
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <algorithm>
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

    RenderPass::~RenderPass() {
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy RenderPass: Logical Device was NULL"
                      << "\n";
        }
        if (this->hRenderPass == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy RenderPass: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyRenderPass(this->pLogicalDevice->getLogicalDeviceHandle(), this->hRenderPass, nullptr);
    }

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
            renderPassBeginInfo.renderArea = {.offset = {0, 0}, .extent = pFramebuffer->getExtent()};
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
} // namespace fillcan