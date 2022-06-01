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

    std::vector<std::shared_ptr<CommandBuffer>> CommandPool::allocateCommandBuffers(VkCommandBufferLevel level, unsigned int commandBufferCount) {
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
        std::vector<std::shared_ptr<CommandBuffer>> allocatedCommandBuffers;
        allocatedCommandBuffers.reserve(commandBufferHandles.size());
        for (VkCommandBuffer& commandBufferHandle : commandBufferHandles) {
            this->commandBuffers.emplace_back(commandBufferHandle, level);
            allocatedCommandBuffers.push_back(std::make_shared<CommandBuffer>(this->commandBuffers.back()));
        }
        return allocatedCommandBuffers;
    }

    void CommandPool::freeCommandBuffers(std::vector<std::shared_ptr<CommandBuffer>> pCommandBuffers) {
        // Get the handle to the VkCommandBuffer from the CommandBuffer wrapper
        std::vector<VkCommandBuffer> commandBuffersToBeFreed = {};
        for (std::shared_ptr<CommandBuffer> pCommandBuffer : pCommandBuffers) {
            commandBuffersToBeFreed.emplace_back(pCommandBuffer->getCommandBufferHandle());
        }

        // Free the command buffers using their handles
        vkFreeCommandBuffers(this->pLogicalDevice->getLogicalDeviceHandle(), this->hCommandPool, commandBuffers.size(),
                             commandBuffersToBeFreed.data());

        // Remove the freed command buffers from the list of command buffers
        for (VkCommandBuffer& freedCommandBuffer : commandBuffersToBeFreed) {
            auto remove_if =
                std::remove_if(this->commandBuffers.begin(), this->commandBuffers.end(), [freedCommandBuffer](CommandBuffer& commandBuffer) {
                    return freedCommandBuffer == commandBuffer.getCommandBufferHandle();
                });
            this->commandBuffers.erase(remove_if, this->commandBuffers.end());
        }
    }

    bool CommandPool::reset(VkCommandPoolResetFlags flags = 0) {
        return vkResetCommandPool(this->pLogicalDevice->getLogicalDeviceHandle(), this->hCommandPool, flags) == VK_SUCCESS ? true : false;
    }
} // namespace fillcan