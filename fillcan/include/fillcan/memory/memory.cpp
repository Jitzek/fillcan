// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstddef>
#include <cstdint>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/memory.hpp>
#include <stdexcept>

namespace fillcan {
    Memory::Memory(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkMemoryPropertyFlagBits flag) : pLogicalDevice(pLogicalDevice), flag(flag) {
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(this->pLogicalDevice->getLogicalDeviceHandle(), pBuffer->getBufferHandle(), &memoryRequirements);
        this->init(memoryRequirements);
    }

    Memory::Memory(LogicalDevice* pLogicalDevice, Image* pImage, VkMemoryPropertyFlagBits flag) : pLogicalDevice(pLogicalDevice), flag(flag) {
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(this->pLogicalDevice->getLogicalDeviceHandle(), pImage->getImageHandle(), &memoryRequirements);
        this->init(memoryRequirements);
    }

    Memory::~Memory() { this->unmap(); }

    void Memory::init(VkMemoryRequirements& memoryRequirements) {
        if (!(memoryRequirements.memoryTypeBits & this->flag)) {
            throw std::runtime_error("Memory property flag is not supported");
        }
        VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
        vkGetPhysicalDeviceMemoryProperties(this->pLogicalDevice->getPhysicalDevice()->getPhysicalDeviceHandle(), &physicalDeviceMemoryProperties);
        unsigned int i = 0;
        for (i = 0; i < physicalDeviceMemoryProperties.memoryTypeCount; i++) {
            if (physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & this->flag) {
                break;
            }
            if (i >= physicalDeviceMemoryProperties.memoryTypeCount) {
                throw std::runtime_error("No memory with the requested requirements could be found");
            }
        }
        VkMemoryAllocateInfo memoryAllocateInfo = {};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.pNext = nullptr;
        memoryAllocateInfo.allocationSize = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = i;
        if (vkAllocateMemory(this->pLogicalDevice->getLogicalDeviceHandle(), &memoryAllocateInfo, nullptr, &this->hMemory) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate memory");
        }
    }

    VkDeviceMemory Memory::getMemoryHandle() { return this->hMemory; }

    void** Memory::map(VkDeviceSize offset, VkDeviceSize size) {
        if (vkMapMemory(this->pLogicalDevice->getLogicalDeviceHandle(), this->hMemory, offset, size, 0, &this->pData) != VK_SUCCESS) {
            throw std::runtime_error("Failed to map memory");
        }
        return &this->pData;
    }

    void** Memory::getData() { return &this->pData; }

    void Memory::unmap() { vkUnmapMemory(this->pLogicalDevice->getLogicalDeviceHandle(), this->hMemory); }

    void Memory::flush(VkDeviceSize offset, VkDeviceSize size) {
        VkMappedMemoryRange mappedMemoryRange = {
            .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE, .pNext = nullptr, .memory = this->hMemory, .offset = offset, .size = size};
        if (vkFlushMappedMemoryRanges(this->pLogicalDevice->getLogicalDeviceHandle(), 1, &mappedMemoryRange) != VK_SUCCESS) {
            throw std::runtime_error("Failed to flush memory ranges");
        }
    }

    void Memory::invalidate(VkDeviceSize offset, VkDeviceSize size) {
        VkMappedMemoryRange mappedMemoryRange = {
            .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE, .pNext = nullptr, .memory = this->hMemory, .offset = offset, .size = size};
        if (vkInvalidateMappedMemoryRanges(this->pLogicalDevice->getLogicalDeviceHandle(), 1, &mappedMemoryRange) != VK_SUCCESS) {
            throw std::runtime_error("Failed to invalidate memory ranges");
        }
    }
} // namespace fillcan