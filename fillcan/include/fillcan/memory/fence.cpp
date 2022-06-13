
// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/memory/fence.hpp>
#include <stdexcept>

namespace fillcan {
    Fence::Fence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags) : pLogicalDevice(pLogicalDevice), flags(flags) {
        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceCreateInfo.pNext = nullptr;
        fenceCreateInfo.flags = this->flags;
        if (vkCreateFence(this->pLogicalDevice->getLogicalDeviceHandle(), &fenceCreateInfo, nullptr, &this->hFence) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create fence");
        }
    }
    Fence::~Fence() { vkDestroyFence(this->pLogicalDevice->getLogicalDeviceHandle(), this->hFence, nullptr); }

    VkFence Fence::getFenceHandle() { return this->hFence; }

    bool Fence::waitFor(uint64_t timeout) {
        return vkWaitForFences(pLogicalDevice->getLogicalDeviceHandle(), 1, &this->hFence, true, timeout) == VK_SUCCESS ? true : false;
    }
} // namespace fillcan