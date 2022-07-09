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
        PipelineLayout(LogicalDevice* pLogicalDevice, std::vector<DescriptorSetLayout*>& pDescriptorSetLayouts,
                       std::vector<PushConstant> pushConstants);
        ~PipelineLayout();

        PipelineLayout(const PipelineLayout&) = delete;
        PipelineLayout& operator=(const PipelineLayout&) = delete;

        VkPipelineLayout getPipelineLayoutHandle();

        std::vector<DescriptorSetLayout*> getDescriptorSetLayouts();

        std::vector<PushConstant>& getPushConstants();

        // PushConstant& getPushConstant(std::string name);

        void pushConstantData(CommandBuffer* pCommandBuffer, std::string name, std::unique_ptr<PushConstantData> upPushConstantData);
    };
} // namespace fillcan