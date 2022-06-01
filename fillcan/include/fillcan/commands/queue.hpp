#pragma once

// vulkan
#include "fillcan/commands/command_recording.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_pool.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Queue {
      private:
        VkQueue hQueue;
        LogicalDevice* pLogicalDevice;
        unsigned int queueFamilyIndex;
        unsigned int queueIndex;
        std::unique_ptr<CommandPool> upCommandPool;
        std::vector<CommandRecording> recordings = {};
      public:
        Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex);
        ~Queue();

        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        CommandRecording& createRecording(unsigned int primaryCommandBufferCount, unsigned int secondaryCommandBufferCount);
        bool submitRecordings(std::vector<CommandRecording*> pCommandRecordings, VkFence fence);
        bool resetRecording(CommandRecording& pCommandRecording);
        void freeRecording(CommandRecording& pCommandRecording);
        bool waitIdle();
    };
} // namespace fillcan