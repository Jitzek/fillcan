#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <cstdint>
#include <memory>
#include <vector>

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
        /**
         * @brief Create a new Buffer Builder.
         *
         * @details The Buffer Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         *
         * @note It is recommended to use the Buffer Director for creating Buffers unless the director doesn't offer the required configuration.
         */
        BufferBuilder();
        ~BufferBuilder();

        /**
         * @brief Set the Logical Device for the Buffer.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Buffer should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Set the flags for the Buffer.
         *
         * @param flags A bitmask of VkBufferCreateFlagBits which are all related to sparse buffers.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCreateFlagBits.html
         */
        void setFlags(VkBufferCreateFlags flags);

        /**
         * @brief Set the size for the Buffer.
         *
         * @param size The size of the buffer, in bytes. (For example, 1MiB is 1024 * 1024).
         */
        void setSize(VkDeviceSize size);

        /**
         * @brief Set the usage for the Buffer.
         *
         * @param usage A bitmask of members of the VkBufferUsageFlagBits-enumerant telling Vulkan how the Buffer will be used.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferUsageFlagBits.html
         */
        void setUsage(VkBufferUsageFlags usage);

        /**
         * @brief Set the sharing mode for the Buffer.
         *
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device. Because Vulkan can run many commands in parallel, some implementations need to know whether the buffer will essentially be
         * used by a single command at a time or possibly by several. Setting sharingMode to VK_SHARING_MODE_EXCLUSIVE tell Vulkan that the buffer
         * will only be used for a single queue, while setting sharingMode to VK_SHARING_MODE_CONCURRENT specifies that the application will use the
         * buffer on multiple queues at once. Using VK_SHARING_MODE_CONCURRENT may result in lower performance on some systems, so unless necessary,
         * sharingMode should be set to VK_SHARING_MODE_EXCLUSIVE.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         */
        void setSharingMode(VkSharingMode sharingMode);

        /**
         * @brief Set the queue family indices for the Buffer.
         *
         * @param queueFamilyIndices An array of queue family indices on which the buffer will be used.
         */
        void setQueueFamilyIndices(std::vector<uint32_t>& queueFamilyIndices);

        /**
         * @brief Get the resulting Buffer.
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         * 
         * @throws std::runtime_error if the Buffer couldn't be created.
         */
        std::unique_ptr<Buffer> getResult();

        /**
         * @brief Reset the Builder to it's default values.
         */
        void reset();
    };
} // namespace fillcan