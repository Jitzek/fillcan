#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class Queue;
    struct CommandRecording {
        Queue* queue;
        std::vector<CommandBuffer*> pPrimaryCommandBuffers = {};
        std::vector<CommandBuffer*> pSecondaryCommandBuffers = {};
        std::vector<VkSemaphore> waitSemaphores = {};
        VkPipelineStageFlags waitDstStageMask = 0;
        std::vector<VkSemaphore> signalSemaphores = {};

        bool endAll();
        bool submitAll(VkFence fence);
        bool resetAll(VkCommandBufferResetFlags flags = 0);
    };
} // namespace fillcan