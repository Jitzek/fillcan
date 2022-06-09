// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/commands/command_pool.hpp>
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <algorithm>
#include <list>
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    CommandPool::CommandPool(LogicalDevice* pLogicalDevice, VkCommandPoolCreateFlags flags, unsigned int queueFamilyIndex)
        : pLogicalDevice(pLogicalDevice), flags(flags), queueFamilyIndex(queueFamilyIndex) {
        VkCommandPoolCreateInfo commandPoolCreateInfo = {};
        commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolCreateInfo.pNext = nullptr;
        commandPoolCreateInfo.flags = this->flags;
        commandPoolCreateInfo.queueFamilyIndex = this->queueFamilyIndex;
        if (vkCreateCommandPool(this->pLogicalDevice->getLogicalDeviceHandle(), &commandPoolCreateInfo, nullptr, &hCommandPool) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create command pool");
        }
    }
    CommandPool::~CommandPool() {}

    std::vector<CommandBuffer*> CommandPool::allocateCommandBuffers(VkCommandBufferLevel level, unsigned int commandBufferCount) {
        std::vector<VkCommandBuffer> commandBufferHandles(commandBufferCount);
        VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.pNext = nullptr;
        commandBufferAllocateInfo.commandPool = this->hCommandPool;
        commandBufferAllocateInfo.level = level;
        commandBufferAllocateInfo.commandBufferCount = commandBufferCount;
        if (vkAllocateCommandBuffers(this->pLogicalDevice->getLogicalDeviceHandle(), &commandBufferAllocateInfo, commandBufferHandles.data()) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate primary command buffers");
        }
        std::vector<CommandBuffer*> allocatedCommandBuffers;
        allocatedCommandBuffers.reserve(commandBufferHandles.size());
        for (VkCommandBuffer& commandBufferHandle : commandBufferHandles) {
            this->upCommandBuffers.emplace_back(std::make_unique<CommandBuffer>(commandBufferHandle, level));
            allocatedCommandBuffers.push_back(this->upCommandBuffers.back().get());
        }
        return allocatedCommandBuffers;
    }

    void CommandPool::freeCommandBuffers(std::vector<CommandBuffer*> pCommandBuffers) {
        // Get the handle to the VkCommandBuffer from the CommandBuffer wrapper
        std::vector<VkCommandBuffer> hCommandBuffersToBeFreed = {};
        for (CommandBuffer* pCommandBuffer : pCommandBuffers) {
            hCommandBuffersToBeFreed.emplace_back(pCommandBuffer->getCommandBufferHandle());
        }

        // Free the command buffers using their handles
        vkFreeCommandBuffers(this->pLogicalDevice->getLogicalDeviceHandle(), this->hCommandPool, hCommandBuffersToBeFreed.size(),
                             hCommandBuffersToBeFreed.data());

        // Remove the freed command buffers from the list of command buffers
        for (VkCommandBuffer& freedCommandBuffer : hCommandBuffersToBeFreed) {
            auto remove_if = std::remove_if(this->upCommandBuffers.begin(), this->upCommandBuffers.end(),
                                            [freedCommandBuffer](std::unique_ptr<CommandBuffer>& commandBuffer) {
                                                return freedCommandBuffer == commandBuffer->getCommandBufferHandle();
                                            });
            this->upCommandBuffers.erase(remove_if, this->upCommandBuffers.end());
        }
    }

    bool CommandPool::reset(VkCommandPoolResetFlags flags = 0) {
        return vkResetCommandPool(this->pLogicalDevice->getLogicalDeviceHandle(), this->hCommandPool, flags) == VK_SUCCESS ? true : false;
    }
} // namespace fillcan