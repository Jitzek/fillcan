// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/logical_device.hpp>

// std
#include <algorithm>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

namespace fillcan {
    LogicalDevice::LogicalDevice(PhysicalDevice* pPhysicalDevice, VkPhysicalDeviceFeatures features) : pPhysicalDevice(pPhysicalDevice) {
        std::set<int> queueFamilyIndices = {pPhysicalDevice->getGraphicsQueueFamilyIndex(), pPhysicalDevice->getPresentQueueFamilyIndex(),
                                            pPhysicalDevice->getComputeQueueFamilyIndex()};

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = {};
        float queuePriority = 1.0f;
        for (int queueFamilyIndex : queueFamilyIndices) {
            if (queueFamilyIndex == -1) {
                throw std::runtime_error("Queue not supported");
            }
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = nullptr;
        deviceCreateInfo.flags = 0;

        deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();

        VkPhysicalDeviceFeatures deviceFeatures = this->pPhysicalDevice->getRequiredFeatures();
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        const std::vector<const char*> deviceExtensions = pPhysicalDevice->getRequiredExtensions();
        deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
        deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (vkCreateDevice(this->pPhysicalDevice->getPhysicalDeviceHandle(), &deviceCreateInfo, nullptr, &this->hLogicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create logical device");
        }

        upGraphicsQueue = std::make_unique<Queue>(this, pPhysicalDevice->getGraphicsQueueFamilyIndex(), 0);
        upPresentQueue = std::make_unique<Queue>(this, pPhysicalDevice->getPresentQueueFamilyIndex(), 0);
        upComputeQueue = std::make_unique<Queue>(this, pPhysicalDevice->getComputeQueueFamilyIndex(), 0);

#ifndef NDEBUG
        std::cout << "Logical Device: " << this->pPhysicalDevice->getProperties().deviceName << " created\n";
#endif
    }

    LogicalDevice::~LogicalDevice() {
        vkDeviceWaitIdle(this->hLogicalDevice);
        vkDestroyDevice(this->hLogicalDevice, nullptr);
    }

    VkDevice LogicalDevice::getLogicalDeviceHandle() {
        return this->hLogicalDevice;
    }
        
    Queue* LogicalDevice::getGraphicsQueue() {
        return this->upGraphicsQueue.get();
    }
    Queue* LogicalDevice::getPresentQueue() {
        return this->upPresentQueue.get();
    }
    Queue* LogicalDevice::getComputeQueue() {
        return this->upComputeQueue.get();
    }

} // namespace fillcan