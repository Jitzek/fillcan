// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_view.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Buffer::Buffer(LogicalDevice* pLogicalDevice, VkBufferCreateFlags& flags, VkDeviceSize& size, VkBufferUsageFlags& usage,
                   VkSharingMode& sharingMode, std::vector<uint32_t> queueFamilyIndices)
        : pLogicalDevice(pLogicalDevice), flags(flags), size(size), usage(usage), sharingMode(sharingMode), queueFamilyIndices(queueFamilyIndices),
          bufferViews((std::vector<std::unique_ptr<BufferView>>){}) {
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

    void Buffer::bindMemory(Memory* pMemory, VkDeviceSize memoryOffset) {
        if (vkBindBufferMemory(this->pLogicalDevice->getLogicalDeviceHandle(), this->hBuffer, pMemory->getMemoryHandle(), memoryOffset) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to bind memory to buffer");
        }
        this->pMemory = pMemory;
    }

    const Memory* Buffer::getMemory() const { return this->pMemory; }

    BufferView* Buffer::createBufferView(VkFormat format, VkDeviceSize size, VkDeviceSize range) {
        // TODO: validate if given format is allowed for this buffer
        // VkFormatProperties formatProperties;
        // vkGetPhysicalDeviceFormatProperties(this->pLogicalDevice->getPhysicalDevice()->getPhysicalDeviceHandle(), format, &formatProperties);

        this->bufferViews.emplace_back(std::make_unique<BufferView>(this->pLogicalDevice, this, format, size, range));
        return this->bufferViews.back().get();
    }

    const std::vector<std::unique_ptr<BufferView>>& Buffer::getBufferViews() const { return this->bufferViews; }
} // namespace fillcan