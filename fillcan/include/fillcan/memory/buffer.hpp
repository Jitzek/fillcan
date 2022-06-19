#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/buffer_view.hpp>

// std
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Memory;
    class BufferView;
    class Image;
    class CommandBuffer;
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
        std::vector<std::unique_ptr<BufferView>> upBufferViews = {};

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

        void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);
        Memory* getMemory() const;

        BufferView* createBufferView(VkFormat format, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);
        std::vector<BufferView*> getBufferViews();

        void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, std::vector<VkBufferCopy>& regions);
        void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout dstLayout, std::vector<VkBufferImageCopy>& regions);
    };
} // namespace fillcan