// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Pipeline::Pipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags,
                       std::vector<PipelineShaderStage> shaderStages, VkPipelineCache pipelineCache, Pipeline* pBasePipeline)
        : pLogicalDevice(pLogicalDevice), pCommandBuffer(pCommandBuffer), flags(flags), shaderStages(shaderStages) {
        for (PipelineShaderStage shaderStage : this->shaderStages) {
            std::vector<DescriptorSetLayout*> shaderStageDescriptorSetLayouts = shaderStage.pShaderModule->getDescriptorSetLayouts();
            if (shaderStage.pShaderModule->getDescriptorSetLayouts().size() > 0 && shaderStage.pShaderModule->getDescriptorPool() != nullptr) {

                this->pDescriptorSetLayouts.insert(this->pDescriptorSetLayouts.begin(), shaderStageDescriptorSetLayouts.begin(),
                                                   shaderStageDescriptorSetLayouts.end());
                std::vector<DescriptorSet*> shaderStageDescriptorSets = shaderStage.pShaderModule->getDescriptorPool()->getDescriptorSets();
                this->pDescriptorSets.insert(this->pDescriptorSets.begin(), shaderStageDescriptorSets.begin(), shaderStageDescriptorSets.end());
            }
        }
        this->layout = std::make_unique<PipelineLayout>(this->pLogicalDevice, this->pDescriptorSetLayouts);
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

    VkPipeline Pipeline::getPipelineHandle() { return this->hPipeline; }

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

    CommandBuffer* Pipeline::getCommandBuffer() { return this->pCommandBuffer; }

    void Pipeline::start() {
        if (this->pCommandBuffer == nullptr) {
            std::runtime_error("Failed to start pipeline because no commandbuffer was bound");
        }
        this->bindToCommandBuffer(this->pCommandBuffer);
        if (this->pDescriptorSets.size() > 0) {
            this->bindDescriptorSets();
        }
    }
} // namespace fillcan