#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    bool CommandRecording::submitAll(VkFence fence) { return this->queue->submitRecordings({this}, fence); }

    bool CommandRecording::endAll() {
        bool successfulEnd = true;
        for (std::shared_ptr<CommandBuffer> primaryCommandBuffer : this->pPrimaryCommandBuffers) {
            successfulEnd = successfulEnd && primaryCommandBuffer->end() ? true : false;
        }
        for (std::shared_ptr<CommandBuffer> secondaryCommandBuffer : this->pSecondaryCommandBuffers) {
            successfulEnd = successfulEnd && secondaryCommandBuffer->end() ? true : false;
        }
        return successfulEnd;
    }

    bool CommandRecording::resetAll(VkCommandBufferResetFlags flags) {
        bool successfulReset = true;
        for (std::shared_ptr<CommandBuffer> primaryCommandBuffer : this->pPrimaryCommandBuffers) {
            successfulReset = successfulReset && primaryCommandBuffer->reset(flags) ? true : false;
        }
        for (std::shared_ptr<CommandBuffer> secondaryCommandBuffer : this->pSecondaryCommandBuffers) {
            successfulReset = successfulReset && secondaryCommandBuffer->reset(flags) ? true : false;
        }
        return successfulReset;
    }
} // namespace fillcan