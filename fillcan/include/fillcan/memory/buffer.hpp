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

        const VkBufferCreateFlags& getFlags() const;
        const VkDeviceSize& getSize() const;
        const VkBufferUsageFlags& getUsage() const;
        const VkSharingMode& getSharingMode() const;
        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        void bindMemory(Memory* pMemory);
        const Memory* getMemory() const;
    };
} // namespace fillcan