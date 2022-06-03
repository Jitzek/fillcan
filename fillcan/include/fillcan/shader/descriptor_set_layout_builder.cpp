// vulkan
#include "fillcan/shader/descriptor_set_layout.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/instance/logical_device.hpp"
#include <fillcan/shader/descriptor_set_layout_builder.hpp>

// std
#include <vector>

namespace fillcan {
    DescriptorSetLayoutBuilder::DescriptorSetLayoutBuilder() {}
    DescriptorSetLayoutBuilder::~DescriptorSetLayoutBuilder() {}

    void DescriptorSetLayoutBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void DescriptorSetLayoutBuilder::addBinding(unsigned int binding, VkDescriptorType descriptorType, unsigned int descriptorCount,
                                                VkShaderStageFlags stageFlags, std::vector<VkSampler> immutableSamplers) {
        bindings.emplace_back(
            (VkDescriptorSetLayoutBinding){.binding = binding,
                                           .descriptorType = descriptorType,
                                           .descriptorCount = descriptorCount,
                                           .stageFlags = stageFlags,
                                           .pImmutableSamplers = immutableSamplers.size() > 0 ? immutableSamplers.data() : nullptr});
    }

    DescriptorSetLayout DescriptorSetLayoutBuilder::getResult() { return DescriptorSetLayout(this->pLogicalDevice, this->bindings); }

    void DescriptorSetLayoutBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->bindings = {};
    }
} // namespace fillcan