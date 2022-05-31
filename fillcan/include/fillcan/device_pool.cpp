// fillcan
#include "fillcan/physical_device.hpp"
#include "vulkan/vulkan_core.h"
#include <algorithm>
#include <fillcan/device_pool.hpp>
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

        std::vector<PhysicalDevice> allPhysicalDevices = {};
        for (VkPhysicalDevice vkPhysicalDevice : allVkPhysicalDevices) {
            allPhysicalDevices.emplace_back(vkPhysicalDevice);
        }

        allPhysicalDevices.erase(std::remove_if(allPhysicalDevices.begin(), allPhysicalDevices.end(),
                                                [requiredDeviceExtensions](PhysicalDevice& physicalDevice) {
                                                    if (!physicalDevice.checkPhysicalDeviceExtensionSupport(requiredDeviceExtensions)) {
                                                        return true;
                                                    }
                                                    return false;
                                                }),
                                 allPhysicalDevices.end());
        this->supportedPhysicalDevices = allPhysicalDevices;
#ifndef NDEBUG
        std::cout << "Supported Device count: " << this->supportedPhysicalDevices.size() << std::endl;
#endif
    }

    DevicePool::~DevicePool() {}
} // namespace fillcan