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

        /**
         * @brief Get the handle to the Vulkan Buffer.
         *
         * @return The handle to the Vulkan Buffer.
         */
        const VkBuffer getBufferHandle() const;

        /**
         * @brief Get the flags given in the Constructor.
         *
         * @return The flags given in the Constructor.
         */
        VkBufferCreateFlags getFlags();

        /**
         * @brief Get the size given in the Constructor.
         *
         * @return The size given in the Constructor.
         */
        VkDeviceSize getSize();

        /**
         * @brief Get the usage given in the Constructor.
         *
         * @return The usage given in the Constructor.
         */
        VkBufferUsageFlags getUsage();

        /**
         * @brief Get the sharing mode given in the Constructor.
         *
         * @return The sharing mode given in the Constructor.
         */
        VkSharingMode getSharingMode();

        /**
         * @brief Get the queue family indices given in the Constructor.
         *
         * @return The queue family indices given in the Constructor.
         */
        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        /**
         * @brief Bind Memory to the Buffer.
         *
         * @param pMemory A pointer to the Memory to bind to the Buffer.
         * @param memoryOffset Specifies the offset in the memory object the Buffer will live. If only one resource will be bound to the memory
         * object, this can be set to 0.
         */
        void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);

        /**
         * @brief Get the Memory bound with Buffer#bindMemory.
         *
         * @return A pointer to the bound Memory, or nullptr if no Memory is bound.
         */
        Memory* getMemory() const;

        /**
         * @brief Create a Buffer View.
         *
         * @param format The format in which to interpret the Buffer.
         * @param offset The Buffer View will be a "window" into the parent buffer. The offset is the number of bytes within the Buffer where the
         * Buffer View should start. To create a Buffer View of the entire Buffer, this must be 0.
         * @param range The number of bytes the Buffer Views will contain from offset. To create a buffer representation of the entire
         * buffer, this must be VK_WHOLE_SIZE.
         * @return The index of the newly created Buffer View.
         */
        unsigned int createBufferView(VkFormat format, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);

        /**
         * @brief Get all the created Buffer Views.
         *
         * @return A list of pointers to the created Buffer Views.
         */
        std::vector<BufferView*> getBufferViews();

        /**
         * @brief Get a pointer to a Buffer View by index.
         *
         * @param index The index the Buffer View to get.
         * @return A pointer to the requested Buffer View.
         */
        BufferView* getBufferView(unsigned int index);

        /**
         * @brief Destroy all created Buffer Views.
         */
        void destroyBufferViews();

        /**
         * @brief Destroy a Buffer View by index.
         *
         * @param index The index of the Buffer View to destroy.
         */
        void destroyBufferView(unsigned int index);

        /**
         * @brief Copy this Buffer's data to a given Buffer.
         *
         * @param pCommandBuffer The Command Buffer to use to execute the copy.
         * @param pBuffer A pointer to the Buffer to copy this Buffer's data to.
         * @param regions An array of VkBufferCopy-structures, each of which describes a region of data to copy.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCopy.html
         */
        void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, std::vector<VkBufferCopy>& regions);

        /**
         * @brief Copy this Buffer's data to a given Image.
         *
         * @param pCommandBuffer The Command Buffer to use to execute the copy.
         * @param pImage A pointer to the Image to copy this Buffer's data to.
         * @param dstLayout The layout of the destination Image subresources for the copy. This should be a member of the VkImageLayout-enumerant.
         * This is most likely either VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL or VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * @param regions An array of VkBufferImageCopy-structures, each of which describe a region of data to copy.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferImageCopy.html
         */
        void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout dstLayout, std::vector<VkBufferImageCopy>& regions);
    };
} // namespace fillcan