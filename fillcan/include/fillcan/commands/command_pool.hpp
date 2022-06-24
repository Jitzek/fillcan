#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_recording.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class CommandPool {
      private:
        VkCommandPool hCommandPool;
        LogicalDevice* pLogicalDevice;
        VkCommandPoolCreateFlags flags;
        unsigned int queueFamilyIndex;
        std::vector<std::unique_ptr<CommandBuffer>> upCommandBuffers = {};

      public:
        CommandPool(LogicalDevice* pLogicalDevice, VkCommandPoolCreateFlags flags, unsigned int queueFamilyIndex);
        ~CommandPool();

        CommandPool(const CommandPool&) = delete;
        CommandPool& operator=(const CommandPool&) = delete;

        std::vector<CommandBuffer*> allocateCommandBuffers(VkCommandBufferLevel level, unsigned int commandBufferCount);
        void freeCommandBuffers(std::vector<CommandBuffer*> pCommandBuffers);

        bool reset(VkCommandPoolResetFlags flags);
    };
} // namespace fillcan