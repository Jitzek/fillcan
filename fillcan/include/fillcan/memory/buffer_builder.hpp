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
    class BufferBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        VkBufferCreateFlags flags = 0;
        VkDeviceSize size = 0;
        VkBufferUsageFlags usage = 0;
        VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        std::vector<uint32_t> queueFamilyIndices = {};

      public:
        BufferBuilder();
        ~BufferBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void setFlags(VkBufferCreateFlags flags);
        void setSize(VkDeviceSize size);
        void setUsage(VkBufferUsageFlags usage);
        void setSharingMode(VkSharingMode sharingMode);
        void setQueueFamilyIndices(std::vector<uint32_t> queueFamilyIndices);

        std::unique_ptr<Buffer> getResult();
        void reset();
    };
} // namespace fillcan