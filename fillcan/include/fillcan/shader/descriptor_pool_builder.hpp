#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <utility>
#include <vector>
#include <memory>

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
        std::vector<std::pair<VkDescriptorType, unsigned int>> descriptorsAndCounts = {};

      public:
        DescriptorPoolBuilder();
        ~DescriptorPoolBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void setFlags(VkDescriptorPoolCreateFlags flags);
        void addSet(DescriptorSetLayout* pDescriptorSetLayout, unsigned int amount);

        void reset();
        std::unique_ptr<DescriptorPool> getResult();
    };
} // namespace fillcan