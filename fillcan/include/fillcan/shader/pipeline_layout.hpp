#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class PipelineLayout {
      private:
        VkPipelineLayout hPipelineLayout;
        LogicalDevice* pLogicalDevice;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts;
        // TODO: Push Constants
      public:
        PipelineLayout(LogicalDevice* pLogicalDevice, std::vector<DescriptorSetLayout*>& pDescriptorSetLayouts /* TODO: Push Constants */);
        ~PipelineLayout();

        VkPipelineLayout getPipelineLayoutHandle();

        std::vector<DescriptorSetLayout*> getDescriptorSetLayouts();
    };
} // namespace fillcan