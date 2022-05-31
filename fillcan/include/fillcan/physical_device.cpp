#include "fillcan/physical_device.hpp"
#include "fillcan/window.hpp"
#include "vulkan/vulkan_core.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fillcan/physical_device.hpp>
#include <vector>

namespace fillcan {
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice hPhysicalDevice) : hPhysicalDevice(hPhysicalDevice) {}

    PhysicalDevice::~PhysicalDevice() {}

    bool PhysicalDevice::checkPhysicalDeviceExtensionSupport(std::vector<const char*> extensions) {
        unsigned int extensionCount;
        vkEnumerateDeviceExtensionProperties(this->hPhysicalDevice, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> allExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(this->hPhysicalDevice, nullptr, &extensionCount, allExtensions.data());

        for (const char* extensionName : extensions) {
            bool extensionFound = false;
            for (const VkExtensionProperties& extensionProperties : allExtensions) {
                if (std::strcmp(extensionName, extensionProperties.extensionName) == 0) {
                    extensionFound = true;
                    break;
                }
            }

            if (!extensionFound) {
                return false;
            }
        }
        return true;
    }

    std::vector<VkPhysicalDeviceFeatures> PhysicalDevice::getPhysicalDeviceFeatures() {
        std::vector<VkPhysicalDeviceFeatures> features;
        vkGetPhysicalDeviceFeatures(this->hPhysicalDevice, features.data());
        return features;
    }

    std::vector<VkPhysicalDeviceProperties> PhysicalDevice::getPhysicalDeviceProperties() {
        std::vector<VkPhysicalDeviceProperties> properties;
        vkGetPhysicalDeviceProperties(this->hPhysicalDevice, properties.data());
        return properties;
    }

    std::vector<VkSurfaceCapabilitiesKHR> PhysicalDevice::getPhysicalDeviceSurfaceCapabilitiesKHR(Window* pWindow) {
        std::vector<VkSurfaceCapabilitiesKHR> surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->hPhysicalDevice, pWindow->getSurface(), surfaceCapabilities.data());
        return surfaceCapabilities;
    }

    std::vector<VkSurfaceFormatKHR> PhysicalDevice::getPhysicalDeviceSurfaceFormatsKHR(Window* pWindow) {
        uint32_t surfaceFormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(this->hPhysicalDevice, pWindow->getSurface(), &surfaceFormatCount, nullptr);
        if (surfaceFormatCount == 0) {
            return {};
        }
        std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(this->hPhysicalDevice, pWindow->getSurface(), &surfaceFormatCount, surfaceFormats.data());
        return surfaceFormats;
    }

    std::vector<VkPresentModeKHR> PhysicalDevice::getPhysicalDeviceSurfacePresentModesKHR(Window* pWindow) {
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(this->hPhysicalDevice, pWindow->getSurface(), &presentModeCount, nullptr);
        if (presentModeCount == 0) {
            return {};
        }
        std::vector<VkPresentModeKHR> presentModes;
        vkGetPhysicalDeviceSurfacePresentModesKHR(this->hPhysicalDevice, pWindow->getSurface(), &presentModeCount, presentModes.data());
        return presentModes;
    }

    std::vector<VkQueueFamilyProperties> PhysicalDevice::getPhysicalDeviceQueueFamilyProperties() {
        uint32_t queueFamilyPropertyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(this->hPhysicalDevice, &queueFamilyPropertyCount, nullptr);
        if (queueFamilyPropertyCount == 0) {
            return {};
        }
        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
        vkGetPhysicalDeviceQueueFamilyProperties(this->hPhysicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());
        return queueFamilyProperties;
    }

    int PhysicalDevice::findGraphicsQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getPhysicalDeviceQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                return i;
            }
        }
        return -1;
    }

    int PhysicalDevice::findPresentQueueFamilyIndex(Window* pWindow, std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getPhysicalDeviceQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            VkBool32 presentSupported = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(this->hPhysicalDevice, i, pWindow->getSurface(), &presentSupported);
            if (queueFamilyProperties[i].queueCount > 0 && presentSupported) {
                return i;
            }
        }
        return -1;
    }

    int PhysicalDevice::findComputeQueueFamilyIndex(std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
        if (queueFamilyProperties.size() <= 0) {
            queueFamilyProperties = this->getPhysicalDeviceQueueFamilyProperties();
        }
        for (size_t i = 0; i < queueFamilyProperties.size(); i++) {
            if (queueFamilyProperties[i].queueCount > 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                return i;
            }
        }
        return -1;
    }
} // namespace fillcan