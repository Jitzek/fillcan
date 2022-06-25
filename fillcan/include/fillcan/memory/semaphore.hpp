#pragma once

#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Semaphore {
      private:
        VkSemaphore hSemaphore;
        LogicalDevice* pLogicalDevice;

      public:
        Semaphore(LogicalDevice* pLogicalDevice);
        ~Semaphore();

        Semaphore(const Semaphore&) = delete;
        Semaphore& operator=(const Semaphore&) = delete;

        VkSemaphore getSemaphoreHandle();
    };
} // namespace fillcan