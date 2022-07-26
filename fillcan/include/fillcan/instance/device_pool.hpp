#pragma once

// fillcan
#include <fillcan/instance/instance.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/instance/physical_device.hpp>
#include <fillcan/window.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class DevicePool {
      private:
        std::vector<PhysicalDevice> supportedPhysicalDevices = {};
        std::unique_ptr<LogicalDevice> upCurrentLogicalDevice;

      public:
        /**
         * @brief Create a new Device Pool.
         *
         * @details Initializes a list of Physical Devices that are supported for the purposes of the implementation.
         *
         * @param pInstance A pointer to the Instance with which the Physical Devices should be enumerated.
         * @param pWindow If not nullptr, a pointer to the Window with which the support for presentation will be determined for the Physical Device.
         * Support for presentation- and graphics operations for the Queues will be ensured as well.
         * @param requiredDeviceExtensions The features a Physical Device should have for the purposes of the application.
         * This should be a VkPhysicalDeviceFeatures-structure where each required feature should be set to true.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html
         * @param requiredDeviceFeatures The extensions a Physical Device should enable for the purposes of the application.
         * This should be a list of strings containing the names of the extensions to enable. The available extensions can be retrieved using
         * vkEnumerateInstanceExtensionProperties()
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html.
         *
         * @throws std::runtime_error if no devices with Vulkan support were found.
         */
        DevicePool(Instance* pInstance, Window* pWindow, std::vector<const char*> requiredDeviceExtensions,
                   VkPhysicalDeviceFeatures requiredDeviceFeatures);
        ~DevicePool();
        DevicePool(const DevicePool&) = delete;
        DevicePool& operator=(const DevicePool&) = delete;

        /**
         * @brief Get the Physical Devices that support the requirements given in the Constructor.
         *
         * @return A list of all the Physical Devices that meet the requirements for the purposes of this implementation.
         */
        std::vector<PhysicalDevice> getSupportedPhysicalDevices();

        /**
         * @brief Select a physical device by index to create a logical device of.
         *
         * @param deviceIndex The index of the physical device within the list of supported physical device.
         *
         * @see DevicePool#getSupportedPhysicalDevices
         *
         * @return A pointer to the created logical device.
         *
         * @throws std::runtime_error if the Logical Device couldn't be created.
         */
        LogicalDevice* selectDevice(unsigned int deviceIndex);

        /**
         * @brief Get the currently selected Logical Device.
         *
         * @see DevicePool#selectDevice
         *
         * @return A pointer to the currently selected Logical Device.
         */
        LogicalDevice* getCurrentDevice();
    };
} // namespace fillcan