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
        /**
         * @brief Create a new Fence.
         *
         * @details The Fence class takes in a pointer to a Logical Device and a bitmask of optional flags and uses this information to construct a
         * new Vulkan Fence which it will wrap around to offer functionality such as: waiting for the fence to be signaled and resetting the fence. A
         * fence is a kind of synchronization primitive. Fences are used when the host has to wait for the device to complete the execution of (large)
         * pieces of work represented by a submission, usually with the help of the operating system.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFence.html
         *
         * @param pLogicalDevice A pointer to the Logical Device the Fence should be associated with.
         * @param flags A bitmask of VkFenceCreateFlagBits which specify the initial state and behaviour of the fence.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFenceCreateFlagBits.html
         */
        Fence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags = 0);
        ~Fence();
        Fence(const Fence&) = delete;
        Fence& operator=(const Fence&) = delete;

        /**
         * @brief Get the handle to the Vulkan Fence.
         *
         * @return The handle to the Vulkan Fence.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFence.html
         */
        const VkFence getFenceHandle() const;

        /**
         * @brief Wait for the Fence to be signaled.
         *
         * @param timeout The time in nanoseconds that the function will wait for it to return. If this value is equal to UINT64_MAX it means that the
         * timeout is effectively disabled. This means that the application will wait until the fences are waiting.
         * @return true if the Fence was succesfully waited for.
         * @return false if the timeout expired.
         */
        bool waitFor(uint64_t timeout = UINT64_MAX);

        bool reset();

        static bool s_waitForAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences, uint64_t timeout = UINT64_MAX);

        static bool s_resetAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences);
    };
} // namespace fillcan