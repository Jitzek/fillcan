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
            if (!pPrimaryCommandBuffer->end()) {
                successfulEnd = false;
            }
        }
        for (CommandBuffer* pSecondaryCommandBuffer : this->pSecondaryCommandBuffers) {
            if (!pSecondaryCommandBuffer->end()) {
                successfulEnd = false;
            }
        }
        return successfulEnd;
    }

    bool CommandRecording::resetAll(VkCommandBufferResetFlags flags) { return this->pQueue->resetRecording(this, flags); }

    void CommandRecording::free() { this->pQueue->freeRecording(this); }

} // namespace fillcan