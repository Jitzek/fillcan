// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <cstdint>
#include <optional>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Memory;
    class Buffer {
      private:
        LogicalDevice* pLogicalDevice;
        VkBuffer hBuffer;
        VkBufferCreateFlags flags;
        VkDeviceSize size;
        VkBufferUsageFlags usage;
        VkSharingMode sharingMode;
        std::vector<uint32_t> queueFamilyIndices;
        Memory* pMemory;
        // TODO: std::vector<BufferViews> bufferViews = {};
      public:
        Buffer(LogicalDevice* pLogicalDevice, VkBufferCreateFlags& flags, VkDeviceSize& size, VkBufferUsageFlags& usage, VkSharingMode& sharingMode,
               std::vector<uint32_t> queueFamilyIndices = {});
        ~Buffer();
        
        VkBuffer getBufferHandle();

        VkBufferCreateFlags getFlags();
        VkDeviceSize getSize();
        VkBufferUsageFlags getUsage();
        VkSharingMode getSharingMode();
        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        void bindMemory(Memory* pMemory);
        const Memory* getMemory() const;
    };
} // namespace fillcan