#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class DescriptorSet {
      private:
        VkDescriptorSet hDescriptorSet;
        LogicalDevice* pLogicalDevice;
        DescriptorSetLayout* pDescriptorSetLayout;

      public:
        DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout);
        ~DescriptorSet();

        VkDescriptorSet getDescriptorSetHandle();
        DescriptorSetLayout* getLayout();
        // TODO: writeImage
        // TODO: writeBuffer
        // TODO: writeTexelBufferView
        // TODO: copy
    };
} // namespace fillcan