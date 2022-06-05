// vulkan
#include "vulkan/vulkan_core.h"

// std

namespace fillcan {
    class LogicalDevice;
    class Memory {
      private:
        LogicalDevice* pLogicalDevice;
        VkDeviceMemory hMemory;
      public:
        Memory();
        ~Memory();
    };
}