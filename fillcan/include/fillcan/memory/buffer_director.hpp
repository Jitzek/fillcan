// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/buffer_builder.hpp>

// std
#include <cstdint>
#include <vector>
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class BufferDirector {
      private:
        BufferBuilder builder;

      public:
        BufferDirector();
        ~BufferDirector();

        std::unique_ptr<Buffer> makeVertexBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size);
    };
} // namespace fillcan