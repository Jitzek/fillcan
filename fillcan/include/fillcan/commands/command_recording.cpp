// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/memory/fence.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    bool CommandRecording::submitAll(Fence* pFence) { return this->pQueue->submitRecordings({this}, pFence); }

    bool CommandRecording::endAll() {
        bool successfulEnd = true;
        for (CommandBuffer* pPrimaryCommandBuffer : this->pPrimaryCommandBuffers) {
            successfulEnd = successfulEnd && pPrimaryCommandBuffer->end() ? true : false;
        }
        for (CommandBuffer* pSecondaryCommandBuffer : this->pSecondaryCommandBuffers) {
            successfulEnd = successfulEnd && pSecondaryCommandBuffer->end() ? true : false;
        }
        return successfulEnd;
    }

    bool CommandRecording::resetAll(VkCommandBufferResetFlags flags) {
        bool successfulReset = true;
        for (CommandBuffer* pPrimaryCommandBuffer : this->pPrimaryCommandBuffers) {
            successfulReset = successfulReset && pPrimaryCommandBuffer->reset(flags) ? true : false;
        }
        for (CommandBuffer* pSecondaryCommandBuffer : this->pSecondaryCommandBuffers) {
            successfulReset = successfulReset && pSecondaryCommandBuffer->reset(flags) ? true : false;
        }
        return successfulReset;
    }
} // namespace fillcan