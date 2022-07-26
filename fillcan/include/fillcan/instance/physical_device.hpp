#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/instance.hpp>
#include <fillcan/window.hpp>

// std
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace fillcan {
    class PhysicalDevice {
      private:
        VkPhysicalDevice hPhysicalDevice;
        Window* pWindow;
        std::vector<const char*> requiredExtensions;
        VkPhysicalDeviceFeatures requiredFeatures;
        std::vector<unsigned int> graphicsQueueFamilyIndices = {};
        std::vector<unsigned int> presentQueueFamilyIndices = {};
        std::vector<unsigned int> computeQueueFamilyIndices = {};

        void findGraphicsQueueFamilyIndices(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
        void findPresentQueueFamilyIndices(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});
        void findComputeQueueFamilyIndices(std::vector<VkQueueFamilyProperties> queueFamilyProperties = {});

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
         * vkEnumerateInstanceExtensionProperties().
         * @see  https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html ).
         */
        PhysicalDevice(VkPhysicalDevice hPhysicalDevice, Window* pWindow, std::vector<const char*> requiredExtensions,
                       VkPhysicalDeviceFeatures requiredFeatures = {});
        ~PhysicalDevice();

        /**
         * @brief Get the handle to the Vulkan Physical Device.
         *
         * @return The handle to the Vulkan Physical Device.
         */
        const VkPhysicalDevice getPhysicalDeviceHandle() const;

        /**
         * @brief Get the device extensions this Physical Device should support.
         *
         * @details The device extensions given in the constructor, @see PhysicalDevice#PhysicalDevice.
         *
         * @return A list of the required device extensions.
         */
        const std::vector<const char*>& getRequiredExtensions() const;

        /**
         * @brief Whether the device extensions given in the constructor are supported.
         * @see PhysicalDevice#PhysicalDevice
         *
         * @return true if the device extensions are supported.
         * @return false if the device extensions aren't supported.
         */
        bool areExtensionsSupported();

        /**
         * @brief Get the device features this Physical Device should support.
         *
         * @details The device features given in the constructor, @see PhysicalDevice#PhysicalDevice.
         *
         * @return A list of the required device features.
         */
        const VkPhysicalDeviceFeatures& getRequiredFeatures() const;

        /**
         * @brief Whether the device features given in the constructor are supported, @see PhysicalDevice#PhysicalDevice.
         *
         * @return true if the device features are supported.
         * @return false if the device features aren't supported.
         */
        bool areFeaturesSupported();

        /**
         * @brief Query all supported and unsupported features for this Physical Device.
         *
         * @return A VkPhysicalDeviceFeatures-structure specifying which features are and aren't supported.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html
         */
        const VkPhysicalDeviceFeatures getFeatures() const;

        /**
         * @brief Query all properties of this Physical Device.
         *
         * @return A VkPhysicalDeviceProperties-structure specifying the properties of this Physical Device.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceProperties.html
         */
        const VkPhysicalDeviceProperties getProperties() const;

        /**
         * @brief Query the basic capabilities of the Window surface, needed in order to create a Swapchain.
         *
         * @return A VkSurfaceCapabilitiesKHR-structure specifying the basic capabilities of the Window surface.
         * @see https://khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceCapabilitiesKHR.html
         */
        const VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR() const;

        /**
         * @brief Query the supported Swapchain format with colorspace pairs for the Window surface.
         *
         * @return A list of VkSurfaceFormatKHR-structures specifying the supported format with colorspace pairs for the Window surface.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceFormatKHR.html
         */
        const std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR() const;

        /**
         * @brief Query the supported Swapchain presentation modes for the Window surface.
         *
         * @return A list of VkPresentModeKHR-structures specifying the supported presentation modes for the Window surface.
         * @see https://khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html
         */
        const std::vector<VkPresentModeKHR> getSurfacePresentModesKHR() const;

        /**
         * @brief Query the properties of the Queues available on this Physical Device.
         *
         * @return A list of VkQueueFamilyProperties-structures specifying the properties of the Queues available on this Physical Device.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkQueueFamilyProperties.html
         */
        const std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const;

        /**
         * @brief Query the properties of a given format for this Physical Device.
         *
         * @param format The format of which to query it's properties for this Physical Device.
         *
         * @return A VkFormatProperties-structure specifying the properties of the given format for this Physical Device.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFormatProperties.html
         */
        const VkFormatProperties getFormatProperties(VkFormat format) const;

        /**
         * @brief Query the memory properties of this Physical Device.
         *
         * @return A VkPhysicalDeviceMemoryProperties-structure specifying the memory properties of this Physical Device.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceMemoryProperties\.html
         */
        const VkPhysicalDeviceMemoryProperties getMemoryProperties() const;

        /**
         * @brief Find a format from a list of given formats which supports the given tiling and features.
         *
         * @param formats The formats to query support for.
         * @param tiling The tiling arrangement of data in an image which the format should support.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkImageTiling.html
         * @param features A bitmask specifying the features supported by a buffer this format should support.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFormatFeatureFlagBits.html
         *
         * @return An optional value of the first format in the list of given formats that supports the given tiling and features or std::nullopt if
         * none of the given formats supports the given tiling and features.
         * @see https://en.cppreference.com/w/cpp/utility/optional/nullopt.
         */
        const std::optional<VkFormat> findSupportedFormat(std::vector<VkFormat> formats, VkImageTiling tiling, VkFormatFeatureFlags features) const;

        /**
         * @brief Get the queue family indices for the graphics Queues.
         *
         * @return The queue family indices for the graphics Queues.
         */
        const std::vector<unsigned int>& getGraphicsQueueFamilyIndices() const;

        /**
         * @brief Get the queue family indices for the present Queues.
         *
         * @return The queue family indices for the present Queues.
         */
        const std::vector<unsigned int>& getPresentQueueFamilyIndices() const;

        /**
         * @brief Get the queue family indices for the compute Queues.
         *
         * @return The queue family indices for the compute Queues.
         */
        const std::vector<unsigned int>& getComputeQueueFamilyIndices() const;
    };
} // namespace fillcan