// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <memory>
#include <stdexcept>

namespace fillcan {
    BufferDirector::BufferDirector() : builder(BufferBuilder()) {}
    BufferDirector::~BufferDirector() {}

    std::unique_ptr<Buffer> BufferDirector::makeVertexBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }
} // namespace fillcan