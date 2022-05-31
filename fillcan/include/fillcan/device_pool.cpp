// fillcan
#include "fillcan/logical_device.hpp"
#include "fillcan/physical_device.hpp"
#include "vulkan/vulkan_core.h"
#include <algorithm>
#include <fillcan/device_pool.hpp>
#include <iostream>
#include <memory>
#include <vector>

namespace fillcan {
    DevicePool::DevicePool(Instance* pInstance, Window* pWindow, std::vector<const char*> requiredDeviceExtensions) {
        unsigned int deviceCount = 0;
        vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, nullptr);
        if (deviceCount == 0) {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }
#ifndef NDEBUG
        std::cout << "Device count: " << deviceCount << std::endl;
#endif
        std::vector<VkPhysicalDevice> allVkPhysicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(pInstance->getInstance(), &deviceCount, allVkPhysicalDevices.data());

        for (VkPhysicalDevice vkPhysicalDevice : allVkPhysicalDevices) {
            this->supportedPhysicalDevices.emplace_back(vkPhysicalDevice);
        }

        // Remove all physical devices that don't meet the requirements
        this->supportedPhysicalDevices.erase(
            std::remove_if(this->supportedPhysicalDevices.begin(), this->supportedPhysicalDevices.end(),
                           [requiredDeviceExtensions, pWindow](PhysicalDevice& physicalDevice) {
                               // Check if the physical device supports the required device extensions
                               if (!physicalDevice.checkPhysicalDeviceExtensionSupport(requiredDeviceExtensions)) {
                                   return true;
                               }

                               // Check if the physical device supports a swapchain
                               std::vector<VkSurfaceFormatKHR> physicalDeviceSurfaceFormatsKHR =
                                   physicalDevice.getPhysicalDeviceSurfaceFormatsKHR(pWindow);
                               if (physicalDeviceSurfaceFormatsKHR.empty()) {
                                   return true;
                               }
                               std::vector<VkPresentModeKHR> physicalDeviceSurfacePresentModesKHR =
                                   physicalDevice.getPhysicalDeviceSurfacePresentModesKHR(pWindow);
                               if (physicalDeviceSurfacePresentModesKHR.empty()) {
                                   return true;
                               }

                               std::vector<VkQueueFamilyProperties> physicalDeviceQueueFamilyProperties =
                                   physicalDevice.getPhysicalDeviceQueueFamilyProperties();

                               // Check if the physical device supports graphics operations
                               if (physicalDevice.findGraphicsQueueFamilyIndex(physicalDeviceQueueFamilyProperties) == -1) {
                                   return true;
                               }

                               // Check if the physical device supports present operations
                               if (physicalDevice.findPresentQueueFamilyIndex(pWindow, physicalDeviceQueueFamilyProperties) == -1) {
                                   return true;
                               }

                               // Check if the physical device supports compute operations
                               if (physicalDevice.findComputeQueueFamilyIndex(physicalDeviceQueueFamilyProperties) == -1) {
                                   return true;
                               }

                               // Check if necessary features are supported
                               VkPhysicalDeviceFeatures physicalDeviceFeatures = physicalDevice.getPhysicalDeviceFeatures();
                               if (!physicalDeviceFeatures.samplerAnisotropy) {
                                   return true;
                               }

                               return false;
                           }),
            this->supportedPhysicalDevices.end());
#ifndef NDEBUG
        std::cout << "Supported Device count: " << this->supportedPhysicalDevices.size() << std::endl;
#endif
    }

    DevicePool::~DevicePool() {}

    std::vector<PhysicalDevice> DevicePool::getSupportedPhysicalDevices() {
        return this->supportedPhysicalDevices;
    }

    LogicalDevice* DevicePool::selectDevice(unsigned int deviceIndex) {
        if (deviceIndex < 0 || deviceIndex > this->supportedPhysicalDevices.size() - 1) {
            return nullptr;
        }
        this->upCurrentLogicalDevice = std::make_unique<LogicalDevice>(&this->supportedPhysicalDevices[deviceIndex]);
        return this->upCurrentLogicalDevice.get();
    }
} // namespace fillcan