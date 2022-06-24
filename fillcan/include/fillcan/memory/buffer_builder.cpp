// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_builder.hpp>
#include <memory>
#include <stdexcept>

namespace fillcan {
    BufferBuilder::BufferBuilder() {}
    BufferBuilder::~BufferBuilder() {}

    void BufferBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void BufferBuilder::setFlags(VkBufferCreateFlags flags) { this->flags = flags; }

    void BufferBuilder::setSize(VkDeviceSize size) { this->size = size; }

    void BufferBuilder::setUsage(VkBufferUsageFlags usage) { this->usage = usage; }

    void BufferBuilder::setSharingMode(VkSharingMode sharingMode) { this->sharingMode = sharingMode; }

    void BufferBuilder::setQueueFamilyIndices(std::vector<uint32_t>& queueFamilyIndices) { this->queueFamilyIndices = queueFamilyIndices; }

    std::unique_ptr<Buffer> BufferBuilder::getResult() {
        return std::move(
            std::make_unique<Buffer>(this->pLogicalDevice, this->flags, this->size, this->usage, this->sharingMode, this->queueFamilyIndices));
    }

    void BufferBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->flags = 0;
        this->size = 0;
        this->usage = 0;
        this->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        this->queueFamilyIndices.clear();
    }
} // namespace fillcan