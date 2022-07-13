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
        /**
         * @brief Create a new Command Buffer.
         *
         * @details The Command Buffer class takes in a handle to a Vulkan Command Buffer and the level of the Command Buffer.
         * With this information the Command Buffer class acts as a wrapper around the Vulkan Command Buffer for beginning, ending and resetting the
         * Command Buffer. All commands for the GPU are stored in a Command Buffer. All functions that perform GPU work do nothing until the Command
         * Buffer is sent to the GPU.
         *
         * @param hCommandBuffer A handle to a VkCommandBuffer.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBuffer.html
         * @param level The level at which the Command Buffer operates. This should be a member of the VkCommandBufferLevel-enumerant.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferLevel.html
         */
        CommandBuffer(VkCommandBuffer hCommandBuffer, VkCommandBufferLevel level);
        ~CommandBuffer();
        CommandBuffer(const CommandBuffer&) = delete;
        CommandBuffer& operator=(const CommandBuffer&) = delete;

        /**
         * @brief Get the handle to the Vulkan Command Buffer.
         *
         * @return The handle to the Vulkan Command Buffer.
         */
        const VkCommandBuffer getCommandBufferHandle() const;

        /**
         * @brief Get the level at which the Command Buffer operates.
         *
         * @return The level at which the Command Buffer operates. This is a member of the VkCommandBufferLevel-enumerant.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferLevel.html
         */
        const VkCommandBufferLevel getLevel() const;

        /**
         * @brief Start the Command Buffer, which resets it to an initial state.
         *
         * @param flags A bitmask of VkCommandBufferUsageFlagBits telling Vulkan how the Command Buffer will be used.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferUsageFlagBits.html
         * @param pSecondaryCommandBufferInheritanceInfo A VkCommandBufferInheritanceInfo-structure used when starting a secondary Command Buffer to
         * define which states are inherited from the primary Command Buffer that calls it. For primary Command Buffers, this pointer is ignored.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferInheritanceInfo.html
         *
         * @return true if the Command Buffer was succesfully started.
         * @return false if the Command Buffer failed to start.
         */
        bool begin(VkCommandBufferUsageFlags flags = 0, VkCommandBufferInheritanceInfo* pSecondaryCommandBufferInheritanceInfo = nullptr);

        /**
         * @brief End the Command Buffer.
         *
         * @details Before the Command Buffer is ready to be sent to the device for execution, we need to tell Vulkan that we're done recording
         * commands in it.
         *
         * @return true if the Command Buffer was succesfully ended.
         * @return false if the Command Buffer failed to end.
         */
        bool end();

        /**
         * @brief Reset the Command Buffer.
         *
         * @details Many applications use a similar set of commands to render all or part of each frame. Therefore, it is likely that similar Command
         * Buffers are included in the application over and over again. Allocating and freeing Command Buffers every frame is a relatively heavy
         * operation. If the application reuses a Command Buffer many times in a row for similar work, it may be more efficient to reset the Command
         * Buffer. This effectively restores the Command Buffer to its original state, but does not necessarily interact with the Command Pool to do
         * so. Therefore, if the Command Buffer dynamically allocates resources from the Command Pool as the Command Buffer grows, the Command Buffer
         * can hold onto those resources and avoid the cost of reallocation the next time it is rebuilt.
         *
         * @param flags Additional actions to perform while resetting the command buffer. This is a bitmask of VkCommandBufferResetFlagBits.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferResetFlagBits.html
         * @return true if the Command Buffer was succesfully reset.
         * @return false if the Command Buffer failed to reset.
         */
        bool reset(VkCommandBufferResetFlags flags = 0);
    };
} // namespace fillcan