#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <memory>
#include <utility>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorPool;
    class DescriptorSetLayout;
    class DescriptorPoolBuilder {
      private:
        struct DescriptorSetInfo {
            VkDescriptorPoolSize poolSize;
            DescriptorSetLayout* pLayout = nullptr;
            std::vector<std::string> names = {};
        };
        LogicalDevice* pLogicalDevice = nullptr;
        VkDescriptorPoolCreateFlags flags = 0;
        unsigned int maxSets = 0;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
        std::vector<VkDescriptorPoolSize> descriptorPoolSizes = {};
        std::vector<DescriptorSetInfo> descriptorSetInfos = {};

      public:
        DescriptorPoolBuilder();
        ~DescriptorPoolBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void setFlags(VkDescriptorPoolCreateFlags flags);
        void addSet(DescriptorSetLayout* pDescriptorSetLayout, unsigned int amount);
        void addSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name);

        void reset();
        std::unique_ptr<DescriptorPool> getResult();
    };
} // namespace fillcan