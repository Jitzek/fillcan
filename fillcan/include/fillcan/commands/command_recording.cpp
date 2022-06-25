// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/memory/fence.hpp>

// std
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace fillcan {
    bool CommandRecording::submit() { return this->pQueue->submitRecordings({this}, this->upFenceWorkCompleted.get()); }

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

    bool CommandRecording::reset(VkCommandBufferResetFlags flags) {
        bool result = this->pQueue->resetRecording(this, flags);
        this->pWaitSemaphores.clear();
        this->waitDstStageMask = 0;
        this->pSignalSemaphores.clear();
        if (upFenceWorkCompleted != nullptr) {
            this->upFenceWorkCompleted->reset();
        }
        return result;
    }

    void CommandRecording::free() { this->pQueue->freeRecording(this); }

    void CommandRecording::createFence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags) {
        this->upFenceWorkCompleted = std::make_unique<Fence>(pLogicalDevice, flags);
    }

    void CommandRecording::waitForFence(uint64_t timeout) { this->upFenceWorkCompleted->waitFor(timeout); }

} // namespace fillcan