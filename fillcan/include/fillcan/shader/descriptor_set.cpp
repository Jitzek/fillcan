// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <vector>

namespace fillcan {
    DescriptorSet::DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout)
        : pLogicalDevice(pLogicalDevice), hDescriptorSet(hDescriptorSet), pDescriptorSetLayout(pDescriptorSetLayout) {}

    DescriptorSet::~DescriptorSet() {}

    VkDescriptorSet DescriptorSet::getDescriptorSetHandle() { return this->hDescriptorSet; }
    DescriptorSetLayout* DescriptorSet::getLayout() { return this->pDescriptorSetLayout; }
} // namespace fillcan