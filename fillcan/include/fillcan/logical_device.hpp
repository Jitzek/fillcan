#pragma once

// fillcan
#include <fillcan/queue.hpp>

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/physical_device.hpp>
#include <fillcan/queue.hpp>

// std
#include <memory>

// std

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

        VkDevice getLogicalDeviceHandle();
        
        Queue* getGraphicsQueue();
        Queue* getPresentQueue();
        Queue* getComputeQueue();
    };
} // namespace fillcan