#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
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
        PushConstantData data;
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

        VkPipelineLayout getPipelineLayoutHandle();

        std::vector<DescriptorSetLayout*> getDescriptorSetLayouts();

      std::vector<PushConstant>& getPushConstants();

      PushConstant& getPushConstant(std::string name);

      void pushConstant(CommandBuffer* pCommandBuffer, PushConstant& pushConstant);
    };
} // namespace fillcan