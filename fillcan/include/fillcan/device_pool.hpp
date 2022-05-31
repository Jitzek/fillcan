#pragma once

// fillcan
#include <fillcan/instance.hpp>
#include <fillcan/logical_device.hpp>
#include <fillcan/window.hpp>
#include <fillcan/physical_device.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class DevicePool {
      private:
        std::vector<PhysicalDevice> supportedPhysicalDevices = {};
        std::unique_ptr<LogicalDevice> upCurrentLogicalDevice;

      public:
        DevicePool(Instance* pInstance, Window* pWindow, std::vector<const char*> requiredDeviceExtensions,
                   VkPhysicalDeviceFeatures requiredDeviceFeatures);
        ~DevicePool();

        DevicePool(const DevicePool&) = delete;
        DevicePool& operator=(const DevicePool&) = delete;

        std::vector<PhysicalDevice> getSupportedPhysicalDevices();
        LogicalDevice* selectDevice(unsigned int deviceIndex);
    };
} // namespace fillcan