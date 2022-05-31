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

        VkPhysicalDevice getPhysicalDeviceHandle();
        Window* getWindow();

        const std::vector<const char*>& getRequiredExtensions() const;
        bool areExtensionsSupported();
        const VkPhysicalDeviceFeatures& getRequiredFeatures() const;
        bool areFeaturesSupported();
        VkPhysicalDeviceFeatures getFeatures();
        VkPhysicalDeviceProperties getProperties();
        VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR();
        std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR();
        std::vector<VkPresentModeKHR> getSurfacePresentModesKHR();
        std::vector<VkQueueFamilyProperties> getQueueFamilyProperties();

        int getGraphicsQueueFamilyIndex();
        int getPresentQueueFamilyIndex();
        int getComputeQueueFamilyIndex();
    };
} // namespace fillcan