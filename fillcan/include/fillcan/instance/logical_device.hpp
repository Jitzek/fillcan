#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
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

        const VkDevice getLogicalDeviceHandle() const;

        const PhysicalDevice* getPhysicalDevice() const;

        void waitIdle();
        
        Queue* getGraphicsQueue() const;
        Queue* getPresentQueue() const;
        Queue* getComputeQueue() const;
    };
} // namespace fillcan