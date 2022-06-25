#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/physical_device.hpp>

// std
#include <memory>

namespace fillcan {
    class LogicalDevice {
      private:
        VkDevice hLogicalDevice;
        PhysicalDevice* pPhysicalDevice;
        std::unique_ptr<Queue> upGraphicsQueue;
        std::unique_ptr<Queue> upPresentQueue;
        std::unique_ptr<Queue> upComputeQueue;

      public:
        LogicalDevice(PhysicalDevice* pPhysicalDevice, VkPhysicalDeviceFeatures features = {});
        ~LogicalDevice();

        LogicalDevice(const LogicalDevice&) = delete;
        LogicalDevice& operator=(const LogicalDevice&) = delete;

        const VkDevice getLogicalDeviceHandle() const;

        PhysicalDevice* getPhysicalDevice();

        void waitIdle();

        Queue* getGraphicsQueue() const;
        Queue* getPresentQueue() const;
        Queue* getComputeQueue() const;

        CommandRecording* beginSingleTimeCommandRecording(Queue* pQueue);
        void endSingleTimeCommandRecording(CommandRecording* pCommandRecording);
    };
} // namespace fillcan