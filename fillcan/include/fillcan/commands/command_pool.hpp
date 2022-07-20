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
        /**
         * @brief Construct a new Command Pool object
         *
         * @details The primary purpose of a Queue is to process work on behalf of the application. Work is represented as a series of commands that
         * are committed to Command Buffers. The application will create Command Buffers with the work to be done and send them to one of the Queues
         * for execution. Before commands can be recorded, a Command Buffer must be created. Command Buffers themselves are not created directly, but
         * allocated from pools, the Command Pool.
         *
         * @param pLogicalDevice
         * @param flags A bitmask of VkCommandPoolCreateFlagBits that specifies usage behavior for the pool and the command buffers assigned to it. In
         * order to be able to call CommandBuffer#reset on the Command Buffers allocated from this Command Pool the flag
         * VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT should be set.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandPoolCreateFlagBits.html
         * @param queueFamilyIndex The family index of Queues where Command Buffers allocated from this pool are sent.
         *
         * @throws std::runtime_error if the Vulkan Command Pool couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkCommandPool.html
         */
        CommandPool(LogicalDevice* pLogicalDevice, VkCommandPoolCreateFlags flags, unsigned int queueFamilyIndex);
        ~CommandPool();
        CommandPool(const CommandPool&) = delete;
        CommandPool& operator=(const CommandPool&) = delete;

        /**
         * @brief Get the handle to the Vulkan Command Pool.
         *
         * @return The handle to the Vulkan Command Pool.
         */
        const VkCommandPool getCommandPoolHandle() const;

        /**
         * @brief Allocate Command Buffers from the pool.
         *
         * @param level The level at which the allocated Command Buffers operate. This should be a member of the VkCommandBufferLevel-enumerant.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferLevel.html
         * @param commandBufferCount The amount of Command Buffers to allocate.
         * @return A list of pointers to the allocated Command Buffers.
         */
        std::vector<CommandBuffer*> allocateCommandBuffers(VkCommandBufferLevel level, unsigned int commandBufferCount);

        /**
         * @brief Free the given Command Buffers.
         *
         * @details Freeing a Command Buffer does not necessarily free all its resources, but returns them to the Command Pool from which they were
         * allocated.
         *
         * @param pCommandBuffers The Command Buffers to free.
         */
        void freeCommandBuffers(std::vector<CommandBuffer*> pCommandBuffers);

        /**
         * @brief Reset the Command Pool.
         *
         * @details Resets all the Command Buffers allocated from this Command Pool.
         *
         * @param flags Additional actions to perform while resetting the command pool. This is a bitmask of VkCommandPoolResetFlagBits.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandPoolResetFlagBits.html
         * @return true if the Command Pool was succesfully reset.
         * @return false if the Command Pool failed to reset.
         */
        bool reset(VkCommandPoolResetFlags flags);
    };
} // namespace fillcan