#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <optional>

namespace fillcan {
    class CommandBuffer {
      private:
        VkCommandBuffer hCommandBuffer;
        VkCommandBufferLevel level;

      public:
        CommandBuffer(VkCommandBuffer hCommandBuffer, VkCommandBufferLevel level);
        ~CommandBuffer();

        VkCommandBuffer getCommandBufferHandle() const;
        VkCommandBufferLevel getLevel() const;

        bool begin(VkCommandBufferUsageFlags flags = 0, VkCommandBufferInheritanceInfo* pSecondaryCommandBufferInheritanceInfo = nullptr);
        bool end();
        bool reset(VkCommandBufferResetFlags flags = 0);
    };
} // namespace fillcan