#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/memory/fence.hpp>
#include <fillcan/memory/semaphore.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class Queue;
    class LogicalDevice;
    struct CommandRecording {
        Queue* pQueue;
        std::vector<CommandBuffer*> pPrimaryCommandBuffers = {};
        std::vector<CommandBuffer*> pSecondaryCommandBuffers = {};
        std::vector<Semaphore*> pWaitSemaphores = {};
        VkPipelineStageFlags waitDstStageMask = 0;
        std::vector<Semaphore*> pSignalSemaphores = {};

        // Automatically set by queue
        std::unique_ptr<Fence> upFenceWorkCompleted = nullptr;

        bool endAll();
        bool submit();
        bool reset(VkCommandBufferResetFlags flags = 0);
        void free();
        void createFence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags = 0);
        void waitForFence(uint64_t timeout = UINT64_MAX);
    };
} // namespace fillcan