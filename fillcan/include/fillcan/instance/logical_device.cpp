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
    LogicalDevice::LogicalDevice(PhysicalDevice* pPhysicalDevice) : pPhysicalDevice(pPhysicalDevice) {
        std::set<int> queueFamilyIndices = {};

        int graphicsQueueFamilyIndex = -1;
        int presentQueueFamilyIndex = -1;
        int computeQueueFamilyIndex = -1;

        if (pPhysicalDevice->getGraphicsQueueFamilyIndices().size() > 0) {
            graphicsQueueFamilyIndex = pPhysicalDevice->getGraphicsQueueFamilyIndices().at(0);
            queueFamilyIndices.insert(graphicsQueueFamilyIndex);
        }
        if (pPhysicalDevice->getPresentQueueFamilyIndices().size() > 0) {
            presentQueueFamilyIndex = pPhysicalDevice->getPresentQueueFamilyIndices().at(0);
            queueFamilyIndices.insert(presentQueueFamilyIndex);
        }
        if (pPhysicalDevice->getComputeQueueFamilyIndices().size() > 0) {
            computeQueueFamilyIndex = pPhysicalDevice->getComputeQueueFamilyIndices().at(0);
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

    const PhysicalDevice* LogicalDevice::getPhysicalDevice() const { return this->pPhysicalDevice; }

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