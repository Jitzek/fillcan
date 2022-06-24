#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

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

        bool reset();

        static bool waitForAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences, uint64_t timeout = UINT64_MAX);

        static bool resetAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences);
    };
} // namespace fillcan