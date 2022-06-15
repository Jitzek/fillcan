#include "fillcan/instance/logical_device.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/memory/semaphore.hpp>

namespace fillcan {
    Semaphore::Semaphore(LogicalDevice* pLogicalDevice) : pLogicalDevice(pLogicalDevice) {
        VkSemaphoreCreateInfo semaphoreCreateInfo = {};
        semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        semaphoreCreateInfo.pNext = nullptr;
        semaphoreCreateInfo.flags = 0;
        if (vkCreateSemaphore(this->pLogicalDevice->getLogicalDeviceHandle(), &semaphoreCreateInfo, nullptr, &this->hSemaphore) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create sempahore");
        }
    }
    Semaphore::~Semaphore() { vkDestroySemaphore(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSemaphore, nullptr); }

    VkSemaphore Semaphore::getSemaphoreHandle() { return this->hSemaphore; }
} // namespace fillcan