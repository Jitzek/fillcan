#pragma once
// vulkan
#include "fillcan/memory/semaphore.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class Queue;
    class Fence;
    struct CommandRecording {
        // Automatically set
        uint64_t id = 0;

        Queue* pQueue;
        std::vector<CommandBuffer*> pPrimaryCommandBuffers = {};
        std::vector<CommandBuffer*> pSecondaryCommandBuffers = {};
        std::vector<Semaphore*> pWaitSemaphores = {};
        VkPipelineStageFlags waitDstStageMask = 0;
        std::vector<Semaphore*> pSignalSemaphores = {};

        bool endAll();
        bool submitAll(Fence* pFence = nullptr);
        bool resetAll(VkCommandBufferResetFlags flags = 0);
        void free();
    };
} // namespace fillcan