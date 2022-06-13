#pragma once

// fillcan
#include "fillcan/commands/command_pool.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/graphics/swapchain.hpp>
#include <fillcan/instance/device_pool.hpp>
#include <fillcan/instance/instance.hpp>
#include <fillcan/instance/physical_device.hpp>
#include <fillcan/window.hpp>

// std
#include <functional>
#include <memory>
#include <vector>

namespace fillcan {
    class Fillcan {
      private:
        std::unique_ptr<Instance> upInstance{};
        std::unique_ptr<Window> upWindow{};
        std::unique_ptr<DevicePool> upDevicePool{};
        std::unique_ptr<Swapchain> upSwapchain{};

      public:
        Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                VkPhysicalDeviceFeatures requiredDeviceFeatures = {});
        ~Fillcan();
        Fillcan(const Fillcan&) = delete;
        Fillcan& operator=(const Fillcan&) = delete;

        void MainLoop(std::function<void()> callback);

        const std::vector<PhysicalDevice> getSupportedPhysicalDevices() const;
        LogicalDevice* selectDevice(unsigned int deviceIndex = 0);

        LogicalDevice* getCurrentDevice();

        Swapchain* createSwapchain(BufferMode bufferMode = FILLCAN_BUFFERING_TRIPLE, VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR);
        Swapchain* recreateSwapchain(BufferMode bufferMode = FILLCAN_BUFFERING_TRIPLE, VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR);
        Swapchain* getSwapchain();
    };
} // namespace fillcan