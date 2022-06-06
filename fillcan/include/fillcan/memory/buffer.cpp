// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <stdexcept>

namespace fillcan {
    Buffer::Buffer(LogicalDevice* pLogicalDevice, VkBufferCreateFlags& flags, VkDeviceSize& size, VkBufferUsageFlags& usage,
                   VkSharingMode& sharingMode, std::vector<uint32_t> queueFamilyIndices)
        : pLogicalDevice(pLogicalDevice), flags(flags), size(size), usage(usage), sharingMode(sharingMode), queueFamilyIndices(queueFamilyIndices) {
        VkBufferCreateInfo bufferCreateInfo = {};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.pNext = nullptr;
        bufferCreateInfo.flags = this->flags;
        bufferCreateInfo.size = this->size;
        bufferCreateInfo.usage = this->usage;
        bufferCreateInfo.sharingMode = this->sharingMode;
        if (this->sharingMode == VK_SHARING_MODE_CONCURRENT) {
            bufferCreateInfo.queueFamilyIndexCount = static_cast<uint32_t>(this->queueFamilyIndices.size());
            bufferCreateInfo.pQueueFamilyIndices = this->queueFamilyIndices.data();
        }

        if (vkCreateBuffer(this->pLogicalDevice->getLogicalDeviceHandle(), &bufferCreateInfo, nullptr, &this->hBuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create buffer");
        }
    }
    Buffer::~Buffer() { vkDestroyBuffer(this->pLogicalDevice->getLogicalDeviceHandle(), this->hBuffer, nullptr); }

    VkBuffer Buffer::getBufferHandle() { return this->hBuffer; }

    VkBufferCreateFlags Buffer::getFlags() { return this->flags; }

    VkDeviceSize Buffer::getSize() { return this->size; }

    VkBufferUsageFlags Buffer::getUsage() { return this->usage; }

    VkSharingMode Buffer::getSharingMode() { return this->sharingMode; }

    const std::vector<uint32_t>& Buffer::getQueueFamilyIndices() const { return this->queueFamilyIndices; }

    void Buffer::bindMemory(Memory* pMemory) {
        // TODO: bind memory
        this->pMemory = pMemory;
    }

    const Memory* Buffer::getMemory() const { return this->pMemory; }
} // namespace fillcan