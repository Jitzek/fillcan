#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_pool.hpp>
#include <fillcan/commands/command_recording.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Fence;
    class Queue {
      private:
        VkQueue hQueue;
        LogicalDevice* pLogicalDevice;
        unsigned int queueFamilyIndex;
        unsigned int queueIndex;
        std::unique_ptr<CommandPool> upCommandPool;
        std::vector<std::unique_ptr<CommandRecording>> upCommandRecordings = {};

      public:
        /**
         * @brief Create a new Queue.
         *
         * @details The Queue class takes a pointer to a Logical Device along with the queue family index and queue index and uses this information to
         * construct a Command Pool. Each device in Vulkan has one or more Queues. The Queue is the part of the device that does the actual work. It
         * can be thought of as a sub-device that exposes a subset of the functionality of the device.
         * Queues are grouped into one or more queue families, each containing one or more Queues. Queues within a single family are essentially
         * identical. Their capabilities are the same, their performance level and access to system resources is the same, and there is no cost (other
         * than synchronization) for transferring work between each other.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Queue should be associated with.
         * @param queueFamilyIndex The index of the chosen queue family.
         * @param queueIndex The index of the chosen queue from the queue family.
         */
        Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex);
        ~Queue();
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        /**
         * @brief Get the handle to the Vulkan Queue.
         *
         * @return The handle to the Vulkan Queue.
         */
        const VkQueue getQueueHandle() const;

        /**
         * @brief Create a Command Recording.
         *
         * @param primaryCommandBufferCount The amount of Primary Command Buffers the Command Recording should contain.
         * @param secondaryCommandBufferCount The amount of Secondary Command Buffers the Command Recording should contain.
         *
         * @return A pointer to the created Command Recording.
         */
        CommandRecording* createRecording(unsigned int primaryCommandBufferCount, unsigned int secondaryCommandBufferCount);

        /**
         * @brief Submit one or more Command Recordings to be executed by the Queue.
         *
         * @param pCommandRecordings The Command Recordings to submit.
         * @param pFence A pointer to a Fence to signal once all submitted Command Buffers have completed execution.
         * @return true if all Command Recordings were succesfully submitted to the Queue.
         * @return false if not all Command Recordings were succesfully submitted to the Queue.
         */
        bool submitRecordings(std::vector<CommandRecording*> pCommandRecordings, Fence* pFence = nullptr);

        /**
         * @brief Reset a Command Recording.
         *
         * @details This will call reset on every Command Buffer in the given Command Recording.
         * @see CommandBuffer#reset
         *
         * @param pCommandRecording The Command Recording to reset.
         * @param flags Additional actions to perform while resetting the Command Buffer. This is a bitmask of VkCommandBufferResetFlagBits.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferResetFlagBits.html
         * @return true if the Command Recording was succesfully reset.
         * @return false if the Command Recording failed to reset.
         */
        bool resetRecording(CommandRecording* pCommandRecording, VkCommandBufferResetFlags flags);

        /**
         * @brief Free a Command Recording.
         *
         * @details This will call freeCommandBuffers on the Command Pool for all the Command Buffers in the given Command Recording.
         * @see CommandPool#freeCommandBuffers.
         *
         * @param pCommandRecording The Command Recording to free.
         */
        void freeRecording(CommandRecording* pCommandRecording);

        /**
         * @brief Wait for the Queue to become idle.
         * @details When waitIdle returns true, all Command Buffers sent to the Queue are guaranteed to be completed.
         *
         * @return true if the Queue was sucessfully waited on.
         * @return false if something went wrong while waiting for the Queue to idle.
         */
        bool waitIdle();
    };
} // namespace fillcan