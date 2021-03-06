// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Pipeline::Pipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                       std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache, Pipeline* pBasePipeline)
        : pLogicalDevice(pLogicalDevice), flags(flags), shaderStages(shaderStages) {
        for (PipelineShaderStage shaderStage : this->shaderStages) {
            std::vector<DescriptorSetLayout*> shaderStageDescriptorSetLayouts = shaderStage.pShaderModule->getDescriptorSetLayouts();
            if (shaderStage.pShaderModule->getDescriptorSetLayouts().size() > 0 && shaderStage.pShaderModule->getDescriptorPool() != nullptr) {
                this->pDescriptorSetLayouts.insert(this->pDescriptorSetLayouts.begin(), shaderStageDescriptorSetLayouts.begin(),
                                                   shaderStageDescriptorSetLayouts.end());
                std::vector<DescriptorSet*> shaderStageDescriptorSets = shaderStage.pShaderModule->getDescriptorPool()->getDescriptorSets();
                this->pDescriptorSets.insert(this->pDescriptorSets.begin(), shaderStageDescriptorSets.begin(), shaderStageDescriptorSets.end());
            }
        }
        this->layout = std::make_unique<PipelineLayout>(this->pLogicalDevice, this->pDescriptorSetLayouts, std::move(pushConstants));
    }
    Pipeline::~Pipeline() {
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Pipeline: Logical Device was NULL"
                      << "\n";
        }
        if (this->hPipeline == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Pipeline: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyPipeline(this->pLogicalDevice->getLogicalDeviceHandle(), this->hPipeline, nullptr);
    }

    const VkPipeline Pipeline::getPipelineHandle() const { return this->hPipeline; }

    PipelineLayout* Pipeline::getPipelineLayout() { return this->layout.get(); }

    void Pipeline::setBindPoint(VkPipelineBindPoint bindPoint) { this->bindPoint = bindPoint; }

    void Pipeline::bindToCommandBuffer(CommandBuffer* pCommandBuffer) {
        if (this->bindPoint == VK_PIPELINE_BIND_POINT_MAX_ENUM) {
            throw std::runtime_error(
                "Pipeline bind point not set before binding command buffer, please use Pipeline::setPipelineBindPoint before calling this function");
        }
        vkCmdBindPipeline(pCommandBuffer->getCommandBufferHandle(), this->bindPoint, this->hPipeline);
        this->pCommandBuffer = pCommandBuffer;
    }

    void Pipeline::bindDescriptorSets() {
        if (this->bindPoint == VK_PIPELINE_BIND_POINT_MAX_ENUM) {
            throw std::runtime_error("Pipeline bind point not set before binding descriptor sets, please use Pipeline::setPipelineBindPoint before "
                                     "calling this function");
        }
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Not bound to a command buffer before binding descriptor sets, please use Pipeline::bindToCommandBuffer before "
                                     "calling this function");
        }
        std::vector<VkDescriptorSet> hDescriptorSets = {};
        hDescriptorSets.reserve(this->pDescriptorSets.size());
        std::transform(this->pDescriptorSets.begin(), this->pDescriptorSets.end(), std::back_inserter(hDescriptorSets),
                       [](DescriptorSet* pDescriptorSet) { return pDescriptorSet->getDescriptorSetHandle(); });
        vkCmdBindDescriptorSets(this->pCommandBuffer->getCommandBufferHandle(), this->bindPoint, this->layout->getPipelineLayoutHandle(), 0,
                                static_cast<uint32_t>(hDescriptorSets.size()), hDescriptorSets.data(), 0, nullptr);
    }

    void Pipeline::bindDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets, unsigned int firstSet) {
        if (this->bindPoint == VK_PIPELINE_BIND_POINT_MAX_ENUM) {
            throw std::runtime_error("Pipeline bind point not set before binding descriptor sets, please use Pipeline::setPipelineBindPoint before "
                                     "calling this function");
        }
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Not bound to a command buffer before binding descriptor sets, please use Pipeline::bindToCommandBuffer before "
                                     "calling this function");
        }
        std::vector<VkDescriptorSet> hDescriptorSets = {};
        hDescriptorSets.reserve(pDescriptorSets.size());
        std::transform(pDescriptorSets.begin(), pDescriptorSets.end(), std::back_inserter(hDescriptorSets),
                       [](DescriptorSet* pDescriptorSet) { return pDescriptorSet->getDescriptorSetHandle(); });
        vkCmdBindDescriptorSets(this->pCommandBuffer->getCommandBufferHandle(), this->bindPoint, this->layout->getPipelineLayoutHandle(), firstSet,
                                static_cast<uint32_t>(hDescriptorSets.size()), hDescriptorSets.data(), 0, nullptr);
    }

    void Pipeline::bindDescriptorSets(std::vector<std::string> names, unsigned int firstSet) {
        std::vector<DescriptorSet*> pDescriptorSets = {};
        pDescriptorSets.reserve(names.size());
        for (std::string& name : names) {
            DescriptorSet* pDescriptorSet = this->getDescriptorSet(name);
            if (pDescriptorSet == nullptr) {
                throw std::runtime_error("Failed to find descriptor set with name: \"" + name + "\"");
            }
            pDescriptorSets.push_back(this->getDescriptorSet(name));
        }
        this->bindDescriptorSets(pDescriptorSets, firstSet);
    }

    std::vector<DescriptorSet*>& Pipeline::getDescriptorSets() { return this->pDescriptorSets; }

    CommandBuffer* Pipeline::getCommandBuffer() { return this->pCommandBuffer; }

    DescriptorSet* Pipeline::getDescriptorSet(std::string name) {
        for (DescriptorSet* pDescriptorSet : this->pDescriptorSets) {
            if (pDescriptorSet->getName() == name) {
                return pDescriptorSet;
            }
        }
        return nullptr;
    }

    void Pipeline::pushConstantData(std::string name, std::unique_ptr<PushConstantData> upPushConstantData) {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error(
                "Not bound to a command buffer before pushing constant data, please use Pipeline::bindToCommandBuffer before calling this function");
        }
        this->layout->pushConstantData(this->pCommandBuffer, name, std::move(upPushConstantData));
    }
} // namespace fillcan