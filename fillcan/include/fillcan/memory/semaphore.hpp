#pragma once

#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Semaphore {
      private:
        VkSemaphore hSemaphore;
        LogicalDevice* pLogicalDevice;

      public:
        /**
         * @brief Create a new Semaphore
         *
         * @details The Semaphore class takes in a pointer to a Logical Device uses this information to construct a new Vulkan Semaphroe
         * A semaphore is a type of synchronization primitive that allows work performed by different queues to be properly planned and coordinated.
         * Semaphores are used to manage the ownership of resources in different queues on a single device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSemaphore.html
         *
         * @param pLogicalDevice A pointer to the Logical Device the Fence should be associated with.
         */
        Semaphore(LogicalDevice* pLogicalDevice);
        ~Semaphore();
        Semaphore(const Semaphore&) = delete;
        Semaphore& operator=(const Semaphore&) = delete;

        /**
         * @brief Get the handle to the Vulkan Semaphore.
         *
         * @return The handle to the Vulkan Semaphore.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSemaphore.html
         */
        const VkSemaphore getSemaphoreHandle() const;
    };
} // namespace fillcan