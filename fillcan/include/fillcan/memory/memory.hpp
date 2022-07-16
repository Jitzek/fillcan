#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class Image;
    class Memory {
      private:
        LogicalDevice* pLogicalDevice;
        VkDeviceMemory hMemory;
        VkMemoryPropertyFlags flags;
        void* pData = nullptr;

        void init(VkMemoryRequirements& memoryRequirements);

      public:
        /**
         * @brief Create a new Memory allocation.
         *
         * @details The Memory class takes a pointer to a Logical Device along with a pointer to a Buffer or Image and required memory properties and
         * uses this information to allocate Memory for a given Buffer or Image. Before a resource, such as a Buffer or Image, can be used by Vulkan
         * to store data, it must be associated with memory. A device memory allocation is represented as a VkDeviceMemory-object.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Memory allocation should be associated with.
         * @param pBuffer A pointer to the Buffer to create a Memory allocation for.
         * @param flags A bitmask of VkMemoryPropertyFlagBits specifying the required properties for the Memory.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkMemoryPropertyFlagBits.html
         */
        Memory(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkMemoryPropertyFlags flags);

        /**
         * @brief Create a new Memory allocation.
         *
         * @details The Memory class takes a pointer to a Logical Device along with a pointer to a Buffer or Image and required memory properties and
         * uses this information to allocate Memory for a given Buffer or Image. Before a resource, such as a Buffer or Image, can be used by Vulkan
         * to store data, it must be associated with memory. A device memory allocation is represented as a VkDeviceMemory-object.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Memory allocation should be associated with.
         * @param pImage A pointer to the Image to create a Memory allocation for.
         * @param flags A bitmask of VkMemoryPropertyFlagBits specifying the required properties for the Memory.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkMemoryPropertyFlagBits.html
         */
        Memory(LogicalDevice* pLogicalDevice, Image* pImage, VkMemoryPropertyFlags flags);

        ~Memory();
        Memory(const Memory&) = delete;
        Memory& operator=(const Memory&) = delete;

        const VkDeviceMemory getMemoryHandle() const;

        /**
         * @brief Allocate memory to get a host usable pointer.
         *
         * @param offset Access to the memory object must be synchronized externally. To assign a range of a memory object, the initial offset in
         * bytes must be specified in offset. To map the entire memory object, this must be 0.
         * @param size Access to the memory object must be synchronized externally. To allocate a range of a memory object, the size in bytes must be
         * specified. To map the entire memory object, it must be VK_WHOLE_SIZE.
         *
         * @return If successful, it returns a pointer to the mapped area. This pointer can then be cast to the
         * appropriate type in the application and dereferenced to read and write the device memory directly.
         *
         * @throws std::runtime_error if the Memory failed to map.
         */
        void** map(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        /**
         * @brief Unmap any mapped memory.
         */
        void unmap();

        /**
         * @brief Return a pointer to the mapped memory area.
         *
         * @return The mapped memory mapped with Memory#map or nullptr if no memory is mapped.
         */
        void** getData();

        /**
         * @brief Flush a mapped memory range.
         *
         * @details If VK_MEMORY_PROPERTY_HOST_COHERENT_BIT is not set in the memory properties of a mapped memory region, it is the responsibility of
         * the application to explicitly flush or invalidate any caches that may be affected by the application.
         * A flush is needed if the host has written to an allocated memory region and wants the device to see the effect of those writes.
         *
         * @param offset The offset of the range of mapped memory to be flushed. To flush the entire memory area, this must be 0.
         * @param size The size of the mapped memory range to be flushed. To flush the entire memory area, it must be VK_WHOLE_SIZE.
         *
         * @throws std::runtime_error if the mapped memory range failed to flush.
         */
        void flush(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);

        /**
         * @brief Invalidate a mapped memory range.
         *
         * @details If VK_MEMORY_PROPERTY_HOST_COHERENT_BIT is not set in the memory properties of a mapped memory region, it is the responsibility of
         * the application to explicitly flush or invalidate any caches that may be affected by the application.
         * An invalidation is needed if the device is writing to a mapped memory region and the host needs to see the effect of the device's writes.
         *
         * @param offset The offset of the range of mapped memory to be invalidated. To invalidate the entire memory area, this must be 0.
         * @param sizeThe size of the mapped memory range to be invalidated. To invalidate the entire memory area, it must be VK_WHOLE_SIZE.
         *
         * @throws std::runtime_error if the mapped memory range failed to invalidate.
         */
        void invalidate(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);
    };
} // namespace fillcan