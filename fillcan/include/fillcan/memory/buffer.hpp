// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/memory.hpp>

// std
#include <cstdint>
#include <optional>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Buffer {
      private:
        LogicalDevice* pLogicalDevice;
        VkBuffer hBuffer;
        VkBufferCreateFlags flags;
        VkDeviceSize size;
        VkBufferUsageFlags usage;
        VkSharingMode sharingMode;
        std::vector<uint32_t> queueFamilyIndices;
        std::optional<Memory> memory;
        // TODO: std::vector<BufferViews> bufferViews = {};
      public:
        Buffer(LogicalDevice* pLogicalDevice, VkBufferCreateFlags& flags, VkDeviceSize& size, VkBufferUsageFlags& usage, VkSharingMode& sharingMode,
               std::vector<uint32_t> queueFamilyIndices = {});
        ~Buffer();
    };
} // namespace fillcan