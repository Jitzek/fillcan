// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_builder.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <memory>
#include <stdexcept>

namespace fillcan {
    BufferDirector::BufferDirector(LogicalDevice* pLogicalDevice) : pLogicalDevice(pLogicalDevice) {}
    BufferDirector::~BufferDirector() {}

    std::unique_ptr<Buffer> BufferDirector::makeVertexBuffer(VkDeviceSize size) {
        BufferBuilder builder = BufferBuilder();
        builder.setLogicalDevice(this->pLogicalDevice);
        builder.setFlags(0);
        builder.setSize(size);
        builder.setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        builder.setQueueFamilyIndices({});
        return std::move(builder.getResult());
    }
} // namespace fillcan