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
    class CommandPool;

    /**
     * @brief The Command Recording structure is used by the Queue to keep track of the information needed for recording commands.
     *
     */
    struct CommandRecording {
        /**
         * @brief The Queue that owns this recording.
         *
         */
        Queue* pQueue;

        /**
         * @brief The Command Pool the Command Buffers were allocated from.
         *
         */
        CommandPool* pCommandPool;

        /**
         * @brief The allocated primary Command Buffers that can be recorded to.
         *
         */
        std::vector<CommandBuffer*> pPrimaryCommandBuffers = {};

        /**
         * @brief The allocated secondary Command Buffers that can be recorded to.
         *
         */
        std::vector<CommandBuffer*> pSecondaryCommandBuffers = {};

        /**
         * @brief A list of pointers to Semaphores to wait for before executing the Command Buffers.
         *
         */
        std::vector<Semaphore*> pWaitSemaphores = {};

        /**
         * @brief An array of pipeline stages, which is a bitmask of VkPipelineStageFlagBits, at which each corresponding semaphore wait will occur.
         *
         * @details The semaphore at index 0 will wait at the pipeline stage at index 0, the semaphore at index 1 will wait at the pipeline stage at
         * index 1, etc.
         *
         */
        VkPipelineStageFlags waitDstStageMask = 0;

        /**
         * @brief A list of pointers to Semaphores that are signaled when the Command Buffers have finished execution.
         *
         */
        std::vector<Semaphore*> pSignalSemaphores = {};

        /**
         * @brief A unique pointer to a Fence that will be signaled once the Command Buffers have finished execution.
         *
         */
        std::unique_ptr<Fence> upFenceWorkCompleted = nullptr;

        /**
         * @brief Ends all Command Buffers.
         *
         * @details Calls CommandBuffer#end on all Command Buffers.
         *
         * @see CommandBuffer#end
         *
         * @return true if all Command Buffers were succesfully ended.
         * @return false if not all Command Buffers could be ended.
         */
        bool endAll();

        /**
         * @brief Submit all this recording to the Queue.
         *
         * @details Calls Queue#submitRecordings for this recording.
         * @see Queue#submitRecordings
         *
         * @return true if the recording was succesfully submitted to the Queue.
         * @return false if the recording failed to submit to the Queue.
         */
        bool submit();

        /**
         * @brief Resets the recording and resets all structure variables to their default values.
         *
         * @details Calls Queue#resetRecording for this recording before resetting all structure variables to their default values.
         *
         * @param flags Additional actions to perform while resetting the Command Buffers. This is a bitmask of VkCommandBufferResetFlagBits.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferResetFlagBits.html
         *
         * @return true if the recording was succesfully reset.
         * @return false if the recording failed to reset.
         */
        bool reset(VkCommandBufferResetFlags flags = 0);

        /**
         * @brief Free this recording.
         *
         * @details Calls Queue#freeRecording for this recording.
         *
         */
        void free();

        /**
         * @brief Create a Fence which will be signaled once this recording has been submitted to the Queue and all work has finished execution.
         *
         * @param pLogicalDevice The Logical Device that should own the Fence.
         * @param flags A bitmask of VkFenceCreateFlagBits specifying the initial state and behavior of the Fence.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFenceCreateFlagBits.html
         */
        void createFence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags = 0);
        
        /**
         * @brief Wait for the Fence defined with CommandRecording#createFence.
         * @see CommandRecording#createFence
         * 
         * @param timeout The timeout period in units of nanoseconds to wait before returning.
         */
        void waitForFence(uint64_t timeout = UINT64_MAX);
    };
} // namespace fillcan