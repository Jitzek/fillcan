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
        Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex);
        ~Queue();

        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        VkQueue getQueueHandle();

        CommandRecording* createRecording(unsigned int primaryCommandBufferCount, unsigned int secondaryCommandBufferCount);
        bool submitRecordings(std::vector<CommandRecording*> pCommandRecordings, Fence* pFence = nullptr);
        bool resetRecording(CommandRecording* pCommandRecording, VkCommandBufferResetFlags flags);
        void freeRecording(CommandRecording* pCommandRecording);
        bool waitIdle();
    };
} // namespace fillcan