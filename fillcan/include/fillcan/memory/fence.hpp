#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>

// std
#include <algorithm>
#include <cstdint>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Fence {
      private:
        LogicalDevice* pLogicalDevice;
        VkFence hFence;
        VkFenceCreateFlags flags;

      public:
        Fence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags = 0);
        ~Fence();

        VkFence getFenceHandle();

        bool waitFor(uint64_t timeout = UINT64_MAX);

        static bool waitForAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences, uint64_t timeout = UINT64_MAX) {
            std::vector<VkFence> hFences;
            hFences.reserve(pFences.size());
            std::transform(pFences.begin(), pFences.end(), std::back_inserter(hFences), [](const Fence* pFence) { return pFence->hFence; });
            return vkWaitForFences(pLogicalDevice->getLogicalDeviceHandle(), static_cast<uint32_t>(hFences.size()), hFences.data(), true, timeout) ==
                           VK_SUCCESS
                       ? true
                       : false;
        }
    };
} // namespace fillcan