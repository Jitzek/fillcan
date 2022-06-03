#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <utility>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorPool;
    class DescriptorSetLayout;
    class DescriptorPoolBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        VkDescriptorPoolCreateFlags flags = 0;
        unsigned int maxSets = 0;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
        // std::vector<VkDescriptorPoolSize> poolSizes = {};
        std::vector<std::pair<VkDescriptorType, unsigned int>> descriptorsAndCounts = {};

      public:
        DescriptorPoolBuilder();
        ~DescriptorPoolBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void setFlags(VkDescriptorPoolCreateFlags flags);
        void addSet(DescriptorSetLayout* pDescriptorSetLayout, unsigned int amount);
        DescriptorPool getResult();
    };
} // namespace fillcan