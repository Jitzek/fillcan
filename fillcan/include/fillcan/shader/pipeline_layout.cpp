// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace fillcan {
    PipelineLayout::PipelineLayout(LogicalDevice* pLogicalDevice, std::vector<DescriptorSetLayout*>& pDescriptorSetLayouts)
        : pLogicalDevice(pLogicalDevice), pDescriptorSetLayouts(pDescriptorSetLayouts) {
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.pNext = nullptr;
        pipelineLayoutCreateInfo.flags = 0;

        std::vector<VkDescriptorSetLayout> hDescriptorSetLayouts = {};
        hDescriptorSetLayouts.reserve(this->pDescriptorSetLayouts.size());
        std::transform(this->pDescriptorSetLayouts.begin(), this->pDescriptorSetLayouts.end(), std::back_inserter(hDescriptorSetLayouts),
                       [](DescriptorSetLayout* pDescriptorSetLayout) { return pDescriptorSetLayout->getDescriptorSetLayoutHandle(); });
        pipelineLayoutCreateInfo.setLayoutCount = static_cast<uint32_t>(hDescriptorSetLayouts.size());
        pipelineLayoutCreateInfo.pSetLayouts = hDescriptorSetLayouts.data();
        // TODO: Push Constants
        pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
        pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(this->pLogicalDevice->getLogicalDeviceHandle(), &pipelineLayoutCreateInfo, nullptr, &this->hPipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }
    PipelineLayout::~PipelineLayout() { vkDestroyPipelineLayout(this->pLogicalDevice->getLogicalDeviceHandle(), this->hPipelineLayout, nullptr); }

    VkPipelineLayout PipelineLayout::getPipelineLayoutHandle() { return this->hPipelineLayout; }

    std::vector<DescriptorSetLayout*> PipelineLayout::getDescriptorSetLayouts() { return this->pDescriptorSetLayouts; }
} // namespace fillcan