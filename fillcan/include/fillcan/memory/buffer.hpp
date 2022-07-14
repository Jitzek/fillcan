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
        /**
         * @brief Create a new Buffer.
         *
         * @details The Buffer class takes a pointer to a Logical Device along with a size and usage and uses this information to create a Vulkan
         * Buffer Object which it will wrap around to offer functionality such as: binding memory, creating and destroying buffer views and copying
         * data. Vulkan Buffers represent linear arrays of data that are used for different purposes by binding them to a Graphics Pipeline or Compute
         * Pipeline via Descriptor Sets or via certain commands, or by specifying them directly as parameters for certain commands.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Buffer should be associated with.
         * @param flags A bitmask of VkBufferCreateFlagBits which are all related to sparse buffers.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCreateFlagBits.html
         * @param size The size of the buffer, in bytes. (For example, 1MiB is 1024 * 1024).
         * @param usage A bitmask of members of the VkBufferUsageFlagBits-enumerant telling Vulkan how the Buffer will be used.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferUsageFlagBits.html
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device. Because Vulkan can run many commands in parallel, some implementations need to know whether the buffer will essentially be
         * used by a single command at a time or possibly by several. Setting sharingMode to VK_SHARING_MODE_EXCLUSIVE tell Vulkan that the buffer
         * will only be used for a single queue, while setting sharingMode to VK_SHARING_MODE_CONCURRENT specifies that the application will use the
         * buffer on multiple queues at once. Using VK_SHARING_MODE_CONCURRENT may result in lower performance on some systems, so unless necessary,
         * sharingMode should be set to VK_SHARING_MODE_EXCLUSIVE.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         * @param queueFamilyIndices A pointer to an array of queue family indices on which the buffer will be used.
         */
        Buffer(LogicalDevice* pLogicalDevice, VkBufferCreateFlags& flags, VkDeviceSize& size, VkBufferUsageFlags& usage, VkSharingMode& sharingMode,
               std::vector<uint32_t> queueFamilyIndices = {});
        ~Buffer();
        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;

        VkBuffer getBufferHandle();

        VkBufferCreateFlags getFlags();

        VkDeviceSize getSize();

        VkBufferUsageFlags getUsage();

        VkSharingMode getSharingMode();

        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);

        Memory* getMemory() const;

        unsigned int createBufferView(VkFormat format, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);

        BufferView* getBufferView(unsigned int index);

        std::vector<BufferView*> getBufferViews();

        void destroyBufferView(unsigned int index);

        void destroyBufferViews();

        void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, std::vector<VkBufferCopy>& regions);

        void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout dstLayout, std::vector<VkBufferImageCopy>& regions);
    };
} // namespace fillcan