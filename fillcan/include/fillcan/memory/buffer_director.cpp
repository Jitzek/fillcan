// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>

// std
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

    std::unique_ptr<Buffer> BufferDirector::makeVertexTransferDestinationBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeUniformBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeStorageBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeUniformTexelBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeStorageTexelBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeIndexBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeIndexTransferDestinationBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeIndirectBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Buffer> BufferDirector::makeStagingBuffer(LogicalDevice* pLogicalDevice, VkDeviceSize size) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setSize(size);
        this->builder.setUsage(VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
        this->builder.setSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        return std::move(this->builder.getResult());
    }
} // namespace fillcan