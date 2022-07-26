// vulkan
#include "fillcan/commands/command_buffer.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace fillcan {
    PipelineLayout::PipelineLayout(LogicalDevice* pLogicalDevice, std::vector<DescriptorSetLayout*>& pDescriptorSetLayouts,
                                   std::vector<PushConstant> pushConstants)
        : pLogicalDevice(pLogicalDevice), pDescriptorSetLayouts(pDescriptorSetLayouts), pushConstants(std::move(pushConstants)) {
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

        std::vector<VkPushConstantRange> pushConstantRanges = {};
        pushConstantRanges.reserve(this->pushConstants.size());
        std::transform(this->pushConstants.begin(), this->pushConstants.end(), std::back_inserter(pushConstantRanges),
                       [](const PushConstant& pushConstant) { return pushConstant.range; });
        pipelineLayoutCreateInfo.pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size());
        pipelineLayoutCreateInfo.pPushConstantRanges = pushConstantRanges.data();

        if (vkCreatePipelineLayout(this->pLogicalDevice->getLogicalDeviceHandle(), &pipelineLayoutCreateInfo, nullptr, &this->hPipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }
    PipelineLayout::~PipelineLayout() { vkDestroyPipelineLayout(this->pLogicalDevice->getLogicalDeviceHandle(), this->hPipelineLayout, nullptr); }

    const VkPipelineLayout PipelineLayout::getPipelineLayoutHandle() const { return this->hPipelineLayout; }

    void PipelineLayout::pushConstantData(CommandBuffer* pCommandBuffer, std::string name, std::unique_ptr<PushConstantData> upPushConstantData) {
        auto pushConstant = std::find_if(this->pushConstants.begin(), this->pushConstants.end(),
                                         [name](PushConstant& pushConstant) -> bool { return pushConstant.name == name; });
        if (pushConstant == this->pushConstants.end()) {
            throw std::runtime_error("Failed to push constant data: Push constant with name: \"" + name + "\" does not exist");
        }
        pushConstant->upData = std::move(upPushConstantData);
        vkCmdPushConstants(pCommandBuffer->getCommandBufferHandle(), this->hPipelineLayout, pushConstant->range.stageFlags,
                           pushConstant->range.offset, pushConstant->range.size, pushConstant->upData.get());
    }
} // namespace fillcan