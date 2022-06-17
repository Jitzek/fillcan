// vulkan
#include "fillcan/memory/buffer.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstddef>
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/render_pass.hpp>

#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

#include <fillcan/memory/buffer.hpp>

// std
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace fillcan {
    GraphicsPipeline::GraphicsPipeline(
        LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
        std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache, Pipeline* pBasePipeline,
        VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState, VkPipelineVertexInputStateCreateInfo* pVertexInputState,
        VkPipelineTessellationStateCreateInfo* pTessellationState, std::vector<VkPipelineViewportStateCreateInfo>& viewportState,
        VkPipelineRasterizationStateCreateInfo* pRasterizationState, VkPipelineMultisampleStateCreateInfo* pMultisampleState,
        VkPipelineDepthStencilStateCreateInfo* pDepthStencilState, VkPipelineColorBlendStateCreateInfo* pColorBlendState,
        VkPipelineDynamicStateCreateInfo* pDynamicState, RenderPass* pRenderPass, unsigned int subpass)
        : Pipeline(pLogicalDevice, pCommandBuffer, flags, shaderStages, std::move(pushConstants), pipelineCache, pBasePipeline), pRenderPass(pRenderPass),
          subpass(subpass) {
        this->setBindPoint(VK_PIPELINE_BIND_POINT_GRAPHICS);
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
            pipelineShaderStageCreateInfo.stage = shaderStage.stage;
            pipelineShaderStageCreateInfo.module = shaderStage.pShaderModule->getShaderModuleHandle();
            pipelineShaderStageCreateInfo.pName = shaderStage.name.c_str();
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
        if (pBasePipeline != nullptr) {
            graphicsPipelineCreateInfo.basePipelineHandle = pBasePipeline->getPipelineHandle();
        } else {
            graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        }
        graphicsPipelineCreateInfo.basePipelineIndex = 0;

        if (vkCreateGraphicsPipelines(this->pLogicalDevice->getLogicalDeviceHandle(), pipelineCache, 1, &graphicsPipelineCreateInfo, nullptr,
                                      &this->hPipeline) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create graphics pipeline");
        }
        Pipeline::hPipeline = this->hPipeline;
    }

    GraphicsPipeline::~GraphicsPipeline() {}

    RenderPass* GraphicsPipeline::getRenderPass() { return this->pRenderPass; }

    void GraphicsPipeline::bindVertexBuffers(std::vector<Buffer*>& pVertexBuffers) {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error(
                "Not bound to a command buffer before binding vertex buffers, please use Pipeline::bindToCommandBuffer before calling this function");
        }
        this->pVertexBuffers = pVertexBuffers;
        std::vector<VkBuffer> hVertexBuffers = {};
        hVertexBuffers.reserve(this->pVertexBuffers.size());
        std::transform(this->pVertexBuffers.begin(), this->pVertexBuffers.end(), std::back_inserter(hVertexBuffers),
                       [](Buffer* pBuffer) { return pBuffer->getBufferHandle(); });
        std::vector<VkDeviceSize> offsets = {};
        offsets.reserve(hVertexBuffers.size());
        for (size_t i = 0; i < this->pVertexBuffers.size(); i++) {
            offsets.push_back(0);
        }
        vkCmdBindVertexBuffers(this->pCommandBuffer->getCommandBufferHandle(), 0, static_cast<uint32_t>(hVertexBuffers.size()), hVertexBuffers.data(),
                               offsets.data());
    }

    void GraphicsPipeline::bindIndexBuffer(Buffer* pIndexBuffer, VkIndexType indexType) {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error(
                "Not bound to a command buffer before binding index buffer, please use Pipeline::bindToCommandBuffer before calling this function");
        }
        this->pIndexBuffer = pIndexBuffer;
        vkCmdBindIndexBuffer(this->pCommandBuffer->getCommandBufferHandle(), this->pIndexBuffer->getBufferHandle(), 0, indexType);
    }

    void GraphicsPipeline::draw(unsigned int vertexCount, unsigned int instanceCount, unsigned int firstVertex, unsigned int firstInstance) {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error(
                "Not bound to a command buffer before drawing, please use Pipeline::bindToCommandBuffer before calling this function");
        }
        vkCmdDraw(this->pCommandBuffer->getCommandBufferHandle(), vertexCount, instanceCount, firstVertex, firstInstance);
    }

    void GraphicsPipeline::drawIndexed(unsigned int indexCount, unsigned int instanceCount, unsigned int firstIndex, unsigned int vertexOffset,
                                       unsigned int firstInstance) {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error(
                "Not bound to a command buffer before drawing, please use Pipeline::bindToCommandBuffer before calling this function");
        }
        vkCmdDrawIndexed(this->pCommandBuffer->getCommandBufferHandle(), indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    }

    void GraphicsPipeline::pushConstant(PushConstant pushConstant) { this->layout->pushConstant(this->pCommandBuffer, pushConstant); }

    PushConstant& GraphicsPipeline::getPushConstant(std::string name) { return this->layout->getPushConstant(name); }

} // namespace fillcan