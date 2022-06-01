#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/instance.hpp>
#include <fillcan/window.hpp>

// std
#include <vector>
#include <string>

namespace fillcan {
    class PhysicalDevice {
      private:
        VkPhysicalDevice hPhysicalDevice;
        Window* pWindow;
        std::vector<const char*> requiredExtensions;
        VkPhysicalDeviceFeatures requiredFeatures;
        int graphicsQueueFamilyIndex = -1;
        int presentQueueFamilyIndex = -1;
        int computeQueueFamilyIndex = -1;

        void findGraphicsAndPresentQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
        void findComputeQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
      public:
        PhysicalDevice(VkPhysicalDevice hPhysicalDevice, Window* pWindow, std::vector<const char *> requiredExtensions, VkPhysicalDeviceFeatures requiredFeatures = {});
        ~PhysicalDevice();

        const VkPhysicalDevice getPhysicalDeviceHandle() const;
        Window* getWindow();

        const std::vector<const char*>& getRequiredExtensions() const;
        bool areExtensionsSupported();
        const VkPhysicalDeviceFeatures& getRequiredFeatures() const;
        bool areFeaturesSupported();
        const VkPhysicalDeviceFeatures getFeatures() const;
        const VkPhysicalDeviceProperties getProperties() const;
        const VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR() const;
        const std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR() const;
        const std::vector<VkPresentModeKHR> getSurfacePresentModesKHR() const;
        const std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const;

        int getGraphicsQueueFamilyIndex();
        int getPresentQueueFamilyIndex();
        int getComputeQueueFamilyIndex();
    };
} // namespace fillcan