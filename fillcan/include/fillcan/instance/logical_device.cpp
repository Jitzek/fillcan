// fillcan
#include "fillcan/commands/command_recording.hpp"
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>

namespace fillcan {
    LogicalDevice::LogicalDevice(PhysicalDevice* pPhysicalDevice, VkPhysicalDeviceFeatures features) : pPhysicalDevice(pPhysicalDevice) {
        int graphicsQueueFamilyIndex = pPhysicalDevice->getGraphicsQueueFamilyIndex();
        int presentQueueFamilyIndex = pPhysicalDevice->getPresentQueueFamilyIndex();
        int computeQueueFamilyIndex = pPhysicalDevice->getComputeQueueFamilyIndex();

        std::set<int> queueFamilyIndices = {};

        if (graphicsQueueFamilyIndex != -1) {
            queueFamilyIndices.insert(graphicsQueueFamilyIndex);
        }
        if (presentQueueFamilyIndex != -1) {
            queueFamilyIndices.insert(presentQueueFamilyIndex);
        }
        if (computeQueueFamilyIndex != -1) {
            queueFamilyIndices.insert(computeQueueFamilyIndex);
        }
        if (queueFamilyIndices.size() == 0) {
            throw std::runtime_error("Queue doesn't support Graphics, Presentation or Computation.");
        }

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = {};
        float queuePriority = 1.0f;
        for (int queueFamilyIndex : queueFamilyIndices) {
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

        if (graphicsQueueFamilyIndex != -1) {
            this->upGraphicsQueue = std::make_unique<Queue>(this, graphicsQueueFamilyIndex, 0);
        }
        if (presentQueueFamilyIndex != -1) {
            this->upPresentQueue = std::make_unique<Queue>(this, presentQueueFamilyIndex, 0);
        }
        if (computeQueueFamilyIndex != -1) {
            this->upComputeQueue = std::make_unique<Queue>(this, computeQueueFamilyIndex, 0);
        }
    }

    LogicalDevice::~LogicalDevice() {
        if (this->hLogicalDevice == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Logical Device: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        this->waitIdle();
        this->upGraphicsQueue.reset();
        this->upPresentQueue.reset();
        this->upComputeQueue.reset();
        vkDestroyDevice(this->hLogicalDevice, nullptr);
    }

    const VkDevice LogicalDevice::getLogicalDeviceHandle() const { return this->hLogicalDevice; }

    PhysicalDevice* LogicalDevice::getPhysicalDevice() { return this->pPhysicalDevice; }

    void LogicalDevice::waitIdle() { vkDeviceWaitIdle(this->hLogicalDevice); }

    Queue* LogicalDevice::getGraphicsQueue() const { return this->upGraphicsQueue.get(); }
    Queue* LogicalDevice::getPresentQueue() const { return this->upPresentQueue.get(); }
    Queue* LogicalDevice::getComputeQueue() const { return this->upComputeQueue.get(); }

    CommandRecording* LogicalDevice::beginSingleTimeCommandRecording(Queue* pQueue) {
        CommandRecording* pCommandRecording = pQueue->createRecording(1, 0);
        pCommandRecording->pPrimaryCommandBuffers[0]->begin();
        return pCommandRecording;
    }

    void LogicalDevice::endSingleTimeCommandRecording(CommandRecording* pCommandRecording) {
        pCommandRecording->endAll();
        pCommandRecording->submit();
        pCommandRecording->pQueue->waitIdle();
        pCommandRecording->free();
    }

} // namespace fillcan