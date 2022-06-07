#pragma once

// vulkan
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/descriptor_set.hpp>

// std
#include <vector>
#include <memory>

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

        VkDescriptorPool getDescriptorPoolHandle();
        std::vector<DescriptorSet*> getDescriptorSets();

        bool freeDescriptorSets();
        bool freeDescriptorSets(std::vector<std::shared_ptr<DescriptorSet>> pDescriptorSets);

        bool reset();
    };
} // namespace fillcan