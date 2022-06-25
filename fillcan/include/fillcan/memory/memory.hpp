#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class Image;
    class Memory {
      private:
        LogicalDevice* pLogicalDevice;
        VkDeviceMemory hMemory;
        VkMemoryPropertyFlags flags;
        void* pData = nullptr;

        void init(VkMemoryRequirements& memoryRequirements);

      public:
        Memory(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkMemoryPropertyFlags flags);
        Memory(LogicalDevice* pLogicalDevice, Image* pImage, VkMemoryPropertyFlags flags);
        ~Memory();

        Memory(const Memory&) = delete;
        Memory& operator=(const Memory&) = delete;

        VkDeviceMemory getMemoryHandle();

        void** map(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
        void unmap();
        void** getData();
        void flush(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
        void invalidate(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
    };
} // namespace fillcan