// fillcan
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <algorithm>
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
    }

    LogicalDevice::~LogicalDevice() {
        this->waitIdle();
        this->upGraphicsQueue.reset();
        this->upPresentQueue.reset();
        this->upComputeQueue.reset();
        vkDestroyDevice(this->hLogicalDevice, nullptr);
    }

    const VkDevice LogicalDevice::getLogicalDeviceHandle() const { return this->hLogicalDevice; }

    const PhysicalDevice* LogicalDevice::getPhysicalDevice() const { return this->pPhysicalDevice; }

    void LogicalDevice::waitIdle() { vkDeviceWaitIdle(this->hLogicalDevice); }

    Queue* LogicalDevice::getGraphicsQueue() const { return this->upGraphicsQueue.get(); }
    Queue* LogicalDevice::getPresentQueue() const { return this->upPresentQueue.get(); }
    Queue* LogicalDevice::getComputeQueue() const { return this->upComputeQueue.get(); }

} // namespace fillcan