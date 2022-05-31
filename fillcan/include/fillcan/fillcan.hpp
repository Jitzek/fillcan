#pragma once

// fillcan
#include "fillcan/device_pool.hpp"
#include "fillcan/physical_device.hpp"
#include <fillcan/instance.hpp>
#include <fillcan/window.hpp>

// std
#include <functional>
#include <memory>
#include <vector>

namespace fillcan {
    class Fillcan {
      private:
        std::unique_ptr<Instance> upInstance;
        std::unique_ptr<Window> upWindow;
        std::unique_ptr<DevicePool> upDevicePool;

      public:
        Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight, VkPhysicalDeviceFeatures requiredDeviceFeatures = {});
        ~Fillcan();
        Fillcan(const Fillcan&) = delete;
        Fillcan& operator=(const Fillcan&) = delete;

        void MainLoop(std::function<void()> callback);

        std::vector<PhysicalDevice> getSupportedPhysicalDevices();
        void selectDevice(unsigned int deviceIndex = 0);
    };
} // namespace fillcan