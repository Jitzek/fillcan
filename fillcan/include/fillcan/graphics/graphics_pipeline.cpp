// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/render_pass.hpp>

#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <stdexcept>
#include <vector>

namespace fillcan {
    GraphicsPipeline::GraphicsPipeline(
        LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
        VkPipelineCache pipelineCache, Pipeline* pBasePipeline, VkPipelineVertexInputStateCreateInfo* pVertexInputState,
        VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState, VkPipelineTessellationStateCreateInfo* pTessellationState,
        std::vector<VkPipelineViewportStateCreateInfo>& viewportState, VkPipelineRasterizationStateCreateInfo* pRasterizationState,
        VkPipelineMultisampleStateCreateInfo* pMultisampleState, VkPipelineDepthStencilStateCreateInfo* pDepthStencilState,
        VkPipelineColorBlendStateCreateInfo* pColorBlendState, VkPipelineDynamicStateCreateInfo* pDynamicState, RenderPass* pRenderPass,
        unsigned int subpass)
        : Pipeline(pLogicalDevice, pCommandBuffer, flags, shaderStages), pRenderPass(pRenderPass), subpass(subpass) {
        VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
        graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        graphicsPipelineCreateInfo.pNext = nullptr;
        graphicsPipelineCreateInfo.flags = this->flags;

        std::vector<VkPipelineShaderStageCreateInfo> pipelineShaderStageCreateInfos = {};
        pipelineShaderStageCreateInfos.reserve(this->shaderStages.size());
        for (PipelineShaderStage& shaderStage : this->shaderStages) {
            VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo = {};
            pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            pipelineShaderStageCreateInfo.pNext = nullptr;
            pipelineShaderStageCreateInfo.flags = 0;
            pipelineShaderStageCreateInfo.stage = this->shaderStages[0].stage;
            pipelineShaderStageCreateInfo.module = this->shaderStages[0].pShaderModule->getShaderModuleHandle();
            pipelineShaderStageCreateInfo.pName = this->shaderStages[0].name.c_str();
            pipelineShaderStageCreateInfos.push_back(pipelineShaderStageCreateInfo);
        }
        graphicsPipelineCreateInfo.stageCount = static_cast<uint32_t>(pipelineShaderStageCreateInfos.size());
        graphicsPipelineCreateInfo.pStages = pipelineShaderStageCreateInfos.data();

        graphicsPipelineCreateInfo.pVertexInputState = pVertexInputState;
        graphicsPipelineCreateInfo.pInputAssemblyState = pInputAssemblyState;
        graphicsPipelineCreateInfo.pTessellationState = pTessellationState;
        if (!viewportState.empty()) {
            graphicsPipelineCreateInfo.pViewportState = viewportState.data();
        } else {
            graphicsPipelineCreateInfo.pViewportState = nullptr;
        }
        graphicsPipelineCreateInfo.pRasterizationState = pRasterizationState;
        graphicsPipelineCreateInfo.pMultisampleState = pMultisampleState;
        graphicsPipelineCreateInfo.pDepthStencilState = pDepthStencilState;
        graphicsPipelineCreateInfo.pColorBlendState = pColorBlendState;
        graphicsPipelineCreateInfo.pDynamicState = pDynamicState;
        graphicsPipelineCreateInfo.layout = this->layout->getPipelineLayoutHandle();
        graphicsPipelineCreateInfo.renderPass = pRenderPass->getRenderPassHandle();
        graphicsPipelineCreateInfo.subpass = this->subpass;
        graphicsPipelineCreateInfo.basePipelineHandle = pBasePipeline->getPipelineHandle();
        graphicsPipelineCreateInfo.basePipelineIndex = 0;

        if (vkCreateGraphicsPipelines(this->pLogicalDevice->getLogicalDeviceHandle(), pipelineCache, 1, &graphicsPipelineCreateInfo, nullptr, &this->hPipeline) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create graphics pipeline");
        }
    }
    GraphicsPipeline::~GraphicsPipeline() { Pipeline::~Pipeline(); }
} // namespace fillcan