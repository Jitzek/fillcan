// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics_pipeline/render_pass.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <stdexcept>

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

    RenderPass::~RenderPass() {}

    VkRenderPass RenderPass::getRenderPassHandle() { return this->hRenderPass; }
} // namespace fillcan