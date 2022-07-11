#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/instance.hpp>
#include <fillcan/window.hpp>

// std
#include <memory>
#include <string>
#include <vector>

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
        /**
         * @brief Create a new Physical Device.
         *
         * @details The Physical Device class takes in a handle to a Vulkan Physical Device, a pointer to the Window (or nullptr) and the required
         * device features and extensions. With this information the Physical Device class acts as a wrapper around the Vulkan Physical Device for
         * requesting information about the Physical Device and it's capabilities.
         *
         * @param hPhysicalDevice A handle to a VkPhysicalDevice.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDevice.html
         * @param pWindow A pointer to the Window, or nullptr.
         * @see Window
         * @param requiredDeviceExtensions The features a Physical Device should have for the purposes of the application.
         * This should be a VkPhysicalDeviceFeatures-structure where each required feature should be set to true.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html
         * @param requiredDeviceFeatures The extensions a Physical Device should enable for the purposes of the application.
         * This should be a list of strings containing the names of the extensions to enable. The available extensions can be retrieved using
         * vkEnumerateInstanceExtensionProperties()
         * @see  https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html ).
         */
        PhysicalDevice(VkPhysicalDevice hPhysicalDevice, Window* pWindow, std::vector<const char*> requiredExtensions,
                       VkPhysicalDeviceFeatures requiredFeatures = {});
        ~PhysicalDevice();

        const VkPhysicalDevice getPhysicalDeviceHandle() const;

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
        const VkFormatProperties getFormatProperties(VkFormat format) const;
        VkFormat findSupportedFormat(std::vector<VkFormat> formats, VkImageTiling tiling, VkFormatFeatureFlags features);

        int getGraphicsQueueFamilyIndex();
        int getPresentQueueFamilyIndex();
        int getComputeQueueFamilyIndex();
    };
} // namespace fillcan