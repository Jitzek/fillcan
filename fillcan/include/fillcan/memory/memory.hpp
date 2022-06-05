// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class Memory {
      private:
        LogicalDevice* pLogicalDevice;
        VkDeviceMemory hMemory;
        VkMemoryPropertyFlagBits flag;

        void init(VkMemoryRequirements& memoryRequirements, VkDeviceSize allocationSize);
      public:
        Memory(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkMemoryPropertyFlagBits flag);
        ~Memory();

        VkDeviceMemory getMemoryHandle();
    };
}