#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    struct CommandRecording {
        std::vector<std::shared_ptr<CommandBuffer>> pPrimaryCommandBuffers = {};
        std::vector<std::shared_ptr<CommandBuffer>> pSecondaryCommandBuffers = {};
        std::vector<VkSemaphore> waitSemaphores = {};
        VkPipelineStageFlags waitDstStageMask = 0;
        std::vector<VkSemaphore> signalSemaphores = {};

        bool resetCommandBuffers(VkCommandBufferResetFlags flags = 0) {
            bool succesfullReset = true;
            for (std::shared_ptr<CommandBuffer> primaryCommandBuffer : this->pPrimaryCommandBuffers) {
                if (!primaryCommandBuffer->reset(flags))
                    succesfullReset = false;
            }
            for (std::shared_ptr<CommandBuffer> secondaryCommandBuffer : this->pSecondaryCommandBuffers) {
                if (!secondaryCommandBuffer->reset(flags))
                    succesfullReset = false;
            }
            return succesfullReset;
        }
    };
} // namespace fillcan