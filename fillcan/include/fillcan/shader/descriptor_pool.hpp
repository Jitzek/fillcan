#pragma once

// vulkan
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/descriptor_set.hpp>

// std
#include <memory>
#include <string>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorPool {
      private:
        VkDescriptorPool hDescriptorPool;
        LogicalDevice* pLogicalDevice;
        VkDescriptorPoolCreateFlags flags;
        unsigned int maxSets;
        std::vector<VkDescriptorPoolSize> poolSizes;
        std::vector<std::unique_ptr<DescriptorSet>> upDescriptorSets = {};

      public:
        DescriptorPool(LogicalDevice* pLogicalDevice, VkDescriptorPoolCreateFlags flags, unsigned int maxSets,
                       std::vector<VkDescriptorPoolSize> poolSizes);
        ~DescriptorPool();

        bool allocateDescriptorSets(std::vector<DescriptorSetLayout*> pDescriptorSetLayouts);
        DescriptorSet* allocateDescriptorSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name);

        VkDescriptorPool getDescriptorPoolHandle();
        std::vector<DescriptorSet*> getDescriptorSets();

        bool freeDescriptorSets();
        bool freeDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets);

        DescriptorSet* getDescriptorSet(std::string name);

        bool reset();
    };
} // namespace fillcan