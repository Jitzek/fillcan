#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance.hpp>
#include "fillcan/window.hpp"

// std
#include <vector>
#include <string>

namespace fillcan {
    class PhysicalDevice {
      private:
        VkPhysicalDevice hPhysicalDevice;
      public:
        PhysicalDevice(VkPhysicalDevice hPhysicalDevice);
        ~PhysicalDevice();

        bool checkPhysicalDeviceExtensionSupport(std::vector<const char*> extensions);
        VkPhysicalDeviceFeatures getPhysicalDeviceFeatures();
        VkPhysicalDeviceProperties getPhysicalDeviceProperties();
        VkSurfaceCapabilitiesKHR getPhysicalDeviceSurfaceCapabilitiesKHR(Window* pWindow);
        std::vector<VkSurfaceFormatKHR> getPhysicalDeviceSurfaceFormatsKHR(Window* pWindow);
        std::vector<VkPresentModeKHR> getPhysicalDeviceSurfacePresentModesKHR(Window* pWindow);
        std::vector<VkQueueFamilyProperties> getPhysicalDeviceQueueFamilyProperties();
        int findGraphicsQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
        int findPresentQueueFamilyIndex(Window* pWindow, std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
        int findComputeQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
    };
} // namespace fillcan