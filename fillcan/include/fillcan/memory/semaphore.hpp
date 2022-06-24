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

        VkSemaphore getSemaphoreHandle();
    };
} // namespace fillcan