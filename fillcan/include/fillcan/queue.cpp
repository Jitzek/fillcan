
// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/logical_device.hpp>
#include <fillcan/queue.hpp>

namespace fillcan {
    Queue::Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex)
        : pLogicalDevice(pLogicalDevice), queueFamilyIndex(queueFamilyIndex), queueIndex(queueIndex) {
            vkGetDeviceQueue(this->pLogicalDevice->getLogicalDeviceHandle(), this->queueFamilyIndex, this->queueIndex, &this->hQueue);
        }
    Queue::~Queue() {}
} // namespace fillcan