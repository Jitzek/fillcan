#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>
#include <string>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class CommandBuffer;

    struct PushConstantData {};

    struct PushConstant {
        std::string name = "undefined";
        VkPushConstantRange range;
        std::unique_ptr<PushConstantData> upData = nullptr;
    };

    class PipelineLayout {
      private:
        VkPipelineLayout hPipelineLayout;
        LogicalDevice* pLogicalDevice;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts;
        std::vector<PushConstant> pushConstants;

      public:
        /**
         * @brief Create a new Pipeline Layout.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Pipeline Layout should be associated with.
         * @param pDescriptorSetLayouts A list of pointers to descriptor set layouts to be bound in the pipeline layout.
         * @param pushConstants A list of push constants to be bound in the pipeline layout.
         *
         * @note It is recommended to not create a Pipeline Layout by it's Constructor as a Pipeline will create a Pipeline Layout as part of it's
         * construction.
         */
        PipelineLayout(LogicalDevice* pLogicalDevice, std::vector<DescriptorSetLayout*>& pDescriptorSetLayouts,
                       std::vector<PushConstant> pushConstants);
        ~PipelineLayout();
        PipelineLayout(const PipelineLayout&) = delete;
        PipelineLayout& operator=(const PipelineLayout&) = delete;

        /**
         * @brief Get the handle to the Vulkan Pipeline Layout.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayout.html
         *
         * @return The handle to the Vulkan Pipeline Layout.
         */
        const VkPipelineLayout getPipelineLayoutHandle() const;

        /**
         * @brief Update the value of a push constant.
         *
         * @param pCommandBuffer A pointer to a command buffer to execute the update with.
         * @param name The name of the push constant to update.
         * @param upPushConstantData A unique pointer to the new value of the push constant, please use std::move to transfer ownership.
         * @see https://en.cppreference.com/w/cpp/memory/unique_ptr
         * @see https://en.cppreference.com/w/cpp/utility/move
         *
         * @throws std::runtime_error if no push constant with the requested name could be found.
         */
        void pushConstantData(CommandBuffer* pCommandBuffer, std::string name, std::unique_ptr<PushConstantData> upPushConstantData);
    };
} // namespace fillcan