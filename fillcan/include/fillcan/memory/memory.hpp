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
        VkMemoryPropertyFlagBits flag;
        void* pData = nullptr;

        void init(VkMemoryRequirements& memoryRequirements);
      public:
        Memory(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkMemoryPropertyFlagBits flag);
        Memory(LogicalDevice* pLogicalDevice, Image* pImage, VkMemoryPropertyFlagBits flag);
        ~Memory();

        VkDeviceMemory getMemoryHandle();

        void** map(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
        void unmap();
        void** getData();
        void flush(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
        void invalidate(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
    };
}