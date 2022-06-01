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

        const VkCommandBuffer getCommandBufferHandle() const;
        const VkCommandBufferLevel getLevel() const;

        bool begin(VkCommandBufferUsageFlags flags, VkCommandBufferInheritanceInfo* pSecondaryCommandBufferInheritanceInfo);
        bool end();
        bool reset(VkCommandBufferResetFlags flags);
    };
} // namespace fillcan