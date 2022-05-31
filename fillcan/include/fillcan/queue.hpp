#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class Queue {
      private:
        VkQueue hQueue;
        LogicalDevice* pLogicalDevice;
        unsigned int queueFamilyIndex;
        unsigned int queueIndex;
      public:
        Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex);
        ~Queue();

        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;
    };
} // namespace fillcan