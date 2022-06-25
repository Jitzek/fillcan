#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout {
      private:
        VkDescriptorSetLayout hDescriptorSetLayout;
        LogicalDevice* pLogicalDevice;
        std::vector<VkDescriptorSetLayoutBinding> bindings;

      public:
        DescriptorSetLayout(LogicalDevice* pLogicalDevice, std::vector<VkDescriptorSetLayoutBinding> bindings);
        ~DescriptorSetLayout();

        DescriptorSetLayout(const DescriptorSetLayout&) = delete;
        DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

        VkDescriptorSetLayout getDescriptorSetLayoutHandle();
        const std::vector<VkDescriptorSetLayoutBinding>& getBindings() const;
    };
} // namespace fillcan