// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/fillcan.hpp>
#include <fillcan/instance/device_pool.hpp>

// std
#include <algorithm>
#include <iostream>

namespace fillcan {
    DevicePool::DevicePool(Instance* pInstance, Window* pWindow, std::vector<const char*> requiredDeviceExtensions,
                           VkPhysicalDeviceFeatures requiredDeviceFeatures) {
        unsigned int deviceCount = 0;
        vkEnumeratePhysicalDevices(pInstance->getInstanceHandle(), &deviceCount, nullptr);
        if (deviceCount == 0) {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }
#ifndef NDEBUG
        std::cout << "Device count: " << deviceCount << std::endl;
#endif
        std::vector<VkPhysicalDevice> allVkPhysicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(pInstance->getInstanceHandle(), &deviceCount, allVkPhysicalDevices.data());

        for (VkPhysicalDevice vkPhysicalDevice : allVkPhysicalDevices) {
            this->supportedPhysicalDevices.emplace_back(vkPhysicalDevice, pWindow, requiredDeviceExtensions, requiredDeviceFeatures);
        }

        // Remove all physical devices that don't meet the requirements
        this->supportedPhysicalDevices.erase(
            std::remove_if(this->supportedPhysicalDevices.begin(), this->supportedPhysicalDevices.end(),
                           [](PhysicalDevice& physicalDevice) {
                               // Check if the physical device supports the required device extensions
                               if (!physicalDevice.areExtensionsSupported()) {
                                   return true;
                               }

                               // Check if the physical device supports the required features
                               if (!physicalDevice.areFeaturesSupported()) {
                                   return true;
                               }

                               // Check if the physical device supports a swapchain
                               std::vector<VkSurfaceFormatKHR> physicalDeviceSurfaceFormatsKHR = physicalDevice.getSurfaceFormatsKHR();
                               if (physicalDeviceSurfaceFormatsKHR.empty()) {
                                   return true;
                               }
                               std::vector<VkPresentModeKHR> physicalDeviceSurfacePresentModesKHR = physicalDevice.getSurfacePresentModesKHR();
                               if (physicalDeviceSurfacePresentModesKHR.empty()) {
                                   return true;
                               }

                               std::vector<VkQueueFamilyProperties> physicalDeviceQueueFamilyProperties = physicalDevice.getQueueFamilyProperties();

                               // Check if the physical device supports graphics operations
                               if (physicalDevice.getGraphicsQueueFamilyIndex() == -1) {
                                   return true;
                               }

                               // Check if the physical device supports present operations
                               if (physicalDevice.getPresentQueueFamilyIndex() == -1) {
                                   return true;
                               }

                               // Check if the physical device supports compute operations
                               if (physicalDevice.getComputeQueueFamilyIndex() == -1) {
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

    std::vector<PhysicalDevice> DevicePool::getSupportedPhysicalDevices() { return this->supportedPhysicalDevices; }

    LogicalDevice* DevicePool::selectDevice(unsigned int deviceIndex) {
        if (deviceIndex < 0 || deviceIndex > this->supportedPhysicalDevices.size() - 1) {
            return nullptr;
        }
        this->upCurrentLogicalDevice = std::make_unique<LogicalDevice>(&this->supportedPhysicalDevices[deviceIndex]);
        return this->upCurrentLogicalDevice.get();
    }

    LogicalDevice* DevicePool::getCurrentDevice() { return this->upCurrentLogicalDevice.get(); }
} // namespace fillcan