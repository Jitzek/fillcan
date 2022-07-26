#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/buffer_builder.hpp>

// std
#include <cstdint>
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class BufferDirector {
      private:
        BufferBuilder builder;

      public:
        /**
         * @brief Create a new Buffer Director.
         *
         * @details The Buffer Director class is part of the creational design pattern to construct complex objects step by step.
         * The director defines the order in which to execute building steps, while the builder provides the implementation for those steps.
         * The Buffer Director defines methods for constructing frequently used Buffer configurations. For it's methods it takes in the Logical Device
         * with which the Buffer should be associated with, the size of the Buffer and it's sharing mode, which will default to
         * VK_SHARING_MODE_EXCLUSIVE most of the time. With this information it will use the Buffer Builder to construct the requested Buffer which it
         * will then return as a unique pointer which ownership will be moved to the application.
         */
        BufferDirector();
        ~BufferDirector();

        /**
         * @brief Create a new Vertex Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeVertexBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                 VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Vertex Buffer which will be used as a destination for a transfer operation.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeVertexTransferDestinationBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                                    VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Uniform Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeUniformBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                  VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Storage Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeStorageBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                  VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Uniform Texel Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeUniformTexelBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                       VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Storage Texel Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeStorageTexelBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                       VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Index Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeIndexBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Index Buffer which will be used as a destination for a transfer operation.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeIndexTransferDestinationBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                                   VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Indirect Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeIndirectBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                   VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Staging Buffer.
         *
         * @param pLogicalDevice The Logical Device the Buffer should be associated with.
         * @param size The size the Buffer should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the buffer will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Buffer, it's ownership will be moved.
         */
        std::unique_ptr<Buffer> makeStagingBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size,
                                                  VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);
    };
} // namespace fillcan