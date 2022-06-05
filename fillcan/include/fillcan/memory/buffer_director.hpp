// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <cstdint>
#include <vector>
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class BufferDirector {
      private:
        LogicalDevice* pLogicalDevice;

      public:
        BufferDirector(LogicalDevice* pLogicalDevice);
        ~BufferDirector();

        std::unique_ptr<Buffer> makeVertexBuffer(VkDeviceSize size);
    };
} // namespace fillcan