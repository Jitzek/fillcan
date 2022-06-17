// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/computing/compute_pipeline.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <stdexcept>

namespace fillcan {
    ComputePipeline::ComputePipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags,
                                     std::vector<PipelineShaderStage> shaderStages, std::vector<PushConstant> pushConstants,
                                     VkPipelineCache pipelineCache, Pipeline* pBasePipeline)
        : Pipeline(pLogicalDevice, pCommandBuffer, flags, shaderStages, pushConstants, pipelineCache, pBasePipeline) {
        this->setBindPoint(VK_PIPELINE_BIND_POINT_COMPUTE);

        VkComputePipelineCreateInfo computePipelineCreateInfo = {};
        computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        computePipelineCreateInfo.pNext = nullptr;
        computePipelineCreateInfo.flags = this->flags;

        // Shader Stage Create Info
        VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo = {};
        pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        pipelineShaderStageCreateInfo.pNext = nullptr;
        pipelineShaderStageCreateInfo.flags = 0;
        pipelineShaderStageCreateInfo.stage = this->shaderStages[0].stage;
        pipelineShaderStageCreateInfo.module = this->shaderStages[0].pShaderModule->getShaderModuleHandle();
        pipelineShaderStageCreateInfo.pName = this->shaderStages[0].name.c_str();
        // pipelineShaderStageCreateInfo.pSpecializationInfo = this->shaderStages[0]. // TODO: Specialization Info
        //

        computePipelineCreateInfo.stage = pipelineShaderStageCreateInfo;
        computePipelineCreateInfo.layout = this->layout->getPipelineLayoutHandle();
        if (pBasePipeline != nullptr) {
            computePipelineCreateInfo.basePipelineHandle = pBasePipeline->getPipelineHandle();
        } else {
            computePipelineCreateInfo.basePipelineHandle = nullptr;
        }
        computePipelineCreateInfo.basePipelineIndex = 0;

        if (vkCreateComputePipelines(this->pLogicalDevice->getLogicalDeviceHandle(), pipelineCache, 1, &computePipelineCreateInfo, nullptr,
                                     &this->hPipeline) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create compute pipeline");
        }
    }

    ComputePipeline::~ComputePipeline() { Pipeline::~Pipeline(); }
} // namespace fillcan