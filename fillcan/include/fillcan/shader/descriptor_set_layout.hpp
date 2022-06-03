#pragma once

// vulkan
#include "vulkan/vulkan_core.h"
#include <vector>

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout {
      private:
        VkDescriptorSetLayout hDescriptorSetLayout;
        LogicalDevice* pLogicalDevice;
        std::vector<VkDescriptorSetLayoutBinding> bindings;
        unsigned int amount = 1;

      public:
        DescriptorSetLayout(LogicalDevice* pLogicalDevice, std::vector<VkDescriptorSetLayoutBinding> bindings, unsigned int amount = 1);
        ~DescriptorSetLayout();

        VkDescriptorSetLayout getDescriptorSetLayoutHandle();
        const std::vector<VkDescriptorSetLayoutBinding>& getBindings() const;
    };
} // namespace fillcan