// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstddef>
#include <cstdint>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/memory.hpp>
#include <stdexcept>

namespace fillcan {
    Memory::Memory(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkMemoryPropertyFlagBits flag) : pLogicalDevice(pLogicalDevice), flag(flag) {
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(this->pLogicalDevice->getLogicalDeviceHandle(), pBuffer->getBufferHandle(), &memoryRequirements);
        this->init(memoryRequirements, pBuffer->getSize());
    }
    Memory::~Memory() {}

    void Memory::init(VkMemoryRequirements& memoryRequirements, VkDeviceSize allocationSize) {
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
        }
        VkMemoryAllocateInfo memoryAllocateInfo = {};
        memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        memoryAllocateInfo.pNext = nullptr;
        memoryAllocateInfo.allocationSize = allocationSize;
        memoryAllocateInfo.memoryTypeIndex = i;
        if (vkAllocateMemory(this->pLogicalDevice->getLogicalDeviceHandle(), &memoryAllocateInfo, nullptr, &this->hMemory) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate memory");
        }
    }

    VkDeviceMemory Memory::getMemoryHandle() {
        return this->hMemory;
    }
} // namespace fillcan