// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <stdexcept>

namespace fillcan {
    CommandBuffer::CommandBuffer(VkCommandBuffer hCommandBuffer, VkCommandBufferLevel level) : hCommandBuffer(hCommandBuffer), level(level) {}
    CommandBuffer::~CommandBuffer() {}

    const VkCommandBuffer CommandBuffer::getCommandBufferHandle() const { return this->hCommandBuffer; }
    const VkCommandBufferLevel CommandBuffer::getLevel() const { return this->level; }

    bool CommandBuffer::begin(VkCommandBufferUsageFlags flags, VkCommandBufferInheritanceInfo* pSecondaryCommandBufferInheritanceInfo) {
        if (this->level == VK_COMMAND_BUFFER_LEVEL_SECONDARY && pSecondaryCommandBufferInheritanceInfo == nullptr) {
            return false;
        }
        VkCommandBufferBeginInfo commandBufferBeginInfo = {};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        commandBufferBeginInfo.pNext = nullptr;
        commandBufferBeginInfo.flags = flags;
        commandBufferBeginInfo.pInheritanceInfo = pSecondaryCommandBufferInheritanceInfo;
        return vkBeginCommandBuffer(this->hCommandBuffer, &commandBufferBeginInfo) == VK_SUCCESS ? true : false;
    }

    bool CommandBuffer::end() { return vkEndCommandBuffer(this->hCommandBuffer) == VK_SUCCESS ? true : false; }

    bool CommandBuffer::reset(VkCommandBufferResetFlags flags) {
        return vkResetCommandBuffer(this->hCommandBuffer, flags) == VK_SUCCESS ? true : false;
    }
} // namespace fillcan