// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/graphics_pipeline_builder.hpp>
#include <fillcan/shader/pipeline_builder.hpp>

// std
#include <array>
#include <memory>
#include <vector>

namespace fillcan {
    GraphicsPipelineBuilder::GraphicsPipelineBuilder() {}
    GraphicsPipelineBuilder::~GraphicsPipelineBuilder() {}

    void GraphicsPipelineBuilder::addShaderStage(PipelineShaderStage pipelineShaderStage) { this->shaderStages.push_back(pipelineShaderStage); }

    void GraphicsPipelineBuilder::setInputAssemblyState(PipelineInputAssemblyState inputAssemblyState) {
        this->upInputAssemblyState = std::make_unique<PipelineInputAssemblyState>(inputAssemblyState);
    }

    void GraphicsPipelineBuilder::setVertexInputState(PipelineVertexInputState vertexInputState) {
        this->upVertexInputState = std::make_unique<PipelineVertexInputState>(vertexInputState);
    }

    void GraphicsPipelineBuilder::setTessellationState(PipelineTessellationState tessellationState) {
        this->upTessellationState = std::make_unique<PipelineTessellationState>(tessellationState);
    }

    void GraphicsPipelineBuilder::addViewportState(PipelineViewPortState viewportState) {
        this->upViewPortStates.push_back(std::move(std::make_unique<PipelineViewPortState>(viewportState)));
    }

    void GraphicsPipelineBuilder::setRasterizationState(PipelineRasterizationState rasterizationState) {
        this->upRasterizationState = std::make_unique<PipelineRasterizationState>(rasterizationState);
    }

    void GraphicsPipelineBuilder::setMultisampleState(PipelineMultisampleState multisampleState) {
        this->upMultisampleState = std::make_unique<PipelineMultisampleState>(multisampleState);
    }

    void GraphicsPipelineBuilder::setDepthStencilState(PipelineDepthStencilState depthStencilState) {
        this->upDepthStencilState = std::make_unique<PipelineDepthStencilState>(depthStencilState);
    }

    void GraphicsPipelineBuilder::setColorBlendState(PipelineColorBlendState colorBlendState) {
        this->upColorBlendState = std::make_unique<PipelineColorBlendState>(colorBlendState);
    }

    void GraphicsPipelineBuilder::setDynamicState(PipelineDynamicState dynamicState) {
        this->upDynamicState = std::make_unique<PipelineDynamicState>(dynamicState);
    }

    void GraphicsPipelineBuilder::setRenderPass(RenderPass* pRenderPass) { this->pRenderPass = pRenderPass; }

    void GraphicsPipelineBuilder::setSubpass(unsigned int subpass) { this->subpass = subpass; }

    void GraphicsPipelineBuilder::reset() {
        PipelineBuilder::reset();
        this->shaderStages.clear();
        this->upVertexInputState = nullptr;
        this->upInputAssemblyState = nullptr;
        this->upTessellationState = nullptr;
        this->upViewPortStates.clear();
        this->upRasterizationState = nullptr;
        this->upMultisampleState = nullptr;
        this->upDepthStencilState = nullptr;
        this->upColorBlendState = nullptr;
        this->upDynamicState = nullptr;
        RenderPass* pRenderPass = nullptr;
        unsigned int subpass = 0;
    }

    std::unique_ptr<GraphicsPipeline> GraphicsPipelineBuilder::getResult() {
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
        if (this->upInputAssemblyState != nullptr) {
            inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            inputAssemblyStateCreateInfo.pNext = nullptr;
            inputAssemblyStateCreateInfo.flags = 0;
            inputAssemblyStateCreateInfo.topology = this->upInputAssemblyState->topology;
            inputAssemblyStateCreateInfo.primitiveRestartEnable = this->upInputAssemblyState->primitiveRestartEnable;
        }

        // TODO: Check whether the descriptions are supported by the device.
        VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
        if (this->upVertexInputState != nullptr) {
            vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            vertexInputStateCreateInfo.pNext = nullptr;
            vertexInputStateCreateInfo.flags = 0;
            vertexInputStateCreateInfo.vertexBindingDescriptionCount =
                static_cast<uint32_t>(this->upVertexInputState->vertexInputBindingDescriptions.size());
            vertexInputStateCreateInfo.pVertexBindingDescriptions = this->upVertexInputState->vertexInputBindingDescriptions.data();
            vertexInputStateCreateInfo.vertexAttributeDescriptionCount =
                static_cast<uint32_t>(this->upVertexInputState->vertexInputAttributeDescriptions.size());
            vertexInputStateCreateInfo.pVertexAttributeDescriptions = this->upVertexInputState->vertexInputAttributeDescriptions.data();
        }

        VkPipelineTessellationStateCreateInfo tessellationStateCreateInfo = {};
        if (this->upTessellationState != nullptr) {
            tessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
            tessellationStateCreateInfo.pNext = nullptr;
            tessellationStateCreateInfo.flags = 0;
            tessellationStateCreateInfo.patchControlPoints = this->upTessellationState->patchControlPoints;
        }

        // TODO: Check whether the amount of viewports is supported by the device
        std::vector<VkPipelineViewportStateCreateInfo> viewPortStateCreateInfos = {};
        viewPortStateCreateInfos.reserve(this->upViewPortStates.size());
        for (std::unique_ptr<PipelineViewPortState>& upViewPortState : this->upViewPortStates) {
            VkPipelineViewportStateCreateInfo viewPortStateCreateInfo = {};
            viewPortStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            viewPortStateCreateInfo.pNext = nullptr;
            viewPortStateCreateInfo.flags = 0;
            viewPortStateCreateInfo.viewportCount = static_cast<uint32_t>(upViewPortState->viewports.size());
            viewPortStateCreateInfo.pViewports = upViewPortState->viewports.data();
            viewPortStateCreateInfo.scissorCount = static_cast<uint32_t>(upViewPortState->scissors.size());
            viewPortStateCreateInfo.pScissors = upViewPortState->scissors.data();
            viewPortStateCreateInfos.push_back(viewPortStateCreateInfo);
        }

        // TODO: Check whether the parameters are supported by the device
        VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
        if (this->upRasterizationState != nullptr) {
            rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            rasterizationStateCreateInfo.pNext = nullptr;
            rasterizationStateCreateInfo.flags = 0;
            rasterizationStateCreateInfo.depthClampEnable = this->upRasterizationState->depthClampEnable;
            rasterizationStateCreateInfo.rasterizerDiscardEnable = this->upRasterizationState->rasterizerDiscardEnable;
            rasterizationStateCreateInfo.polygonMode = this->upRasterizationState->polygonMode;
            rasterizationStateCreateInfo.cullMode = this->upRasterizationState->cullmode;
            rasterizationStateCreateInfo.frontFace = this->upRasterizationState->frontFace;
            rasterizationStateCreateInfo.depthBiasEnable = this->upRasterizationState->depthBiasEnable;
            rasterizationStateCreateInfo.depthBiasConstantFactor = this->upRasterizationState->depthBiasConstantFactor;
            rasterizationStateCreateInfo.depthBiasClamp = this->upRasterizationState->depthBiasClamp;
            rasterizationStateCreateInfo.depthBiasSlopeFactor = this->upRasterizationState->depthBiasSlopeFactor;
            rasterizationStateCreateInfo.lineWidth = this->upRasterizationState->lineWidth;
        }

        VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
        if (upMultisampleState != nullptr) {
            multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            multisampleStateCreateInfo.pNext = nullptr;
            multisampleStateCreateInfo.flags = 0;
            multisampleStateCreateInfo.rasterizationSamples = this->upMultisampleState->rasterizationSamples;
            multisampleStateCreateInfo.sampleShadingEnable = this->upMultisampleState->sampleShadingEnable;
            multisampleStateCreateInfo.minSampleShading = this->upMultisampleState->minSampleShading;
            multisampleStateCreateInfo.pSampleMask = this->upMultisampleState->sampleMask.data();
            multisampleStateCreateInfo.alphaToCoverageEnable = this->upMultisampleState->alphaToCoverageEnable;
            multisampleStateCreateInfo.alphaToOneEnable = this->upMultisampleState->alphaToOneEnable;
        }

        VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {};
        if (this->upDepthStencilState != nullptr) {
            depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
            depthStencilStateCreateInfo.pNext = nullptr;
            depthStencilStateCreateInfo.flags = 0;
            depthStencilStateCreateInfo.depthTestEnable = this->upDepthStencilState->depthTestEnable;
            depthStencilStateCreateInfo.depthWriteEnable = this->upDepthStencilState->depthWriteEnable;
            depthStencilStateCreateInfo.depthCompareOp = this->upDepthStencilState->depthCompareOp;
            depthStencilStateCreateInfo.depthBoundsTestEnable = this->upDepthStencilState->depthBoundsTestEnable;
            depthStencilStateCreateInfo.stencilTestEnable = this->upDepthStencilState->stencilTestEnable;
            depthStencilStateCreateInfo.front = this->upDepthStencilState->front;
            depthStencilStateCreateInfo.back = this->upDepthStencilState->back;
            depthStencilStateCreateInfo.minDepthBounds = this->upDepthStencilState->minDepthBounds;
            depthStencilStateCreateInfo.maxDepthBounds = this->upDepthStencilState->maxDepthBounds;
        }

        VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
        if (this->upColorBlendState != nullptr) {
            colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            colorBlendStateCreateInfo.pNext = nullptr;
            colorBlendStateCreateInfo.flags = 0;
            colorBlendStateCreateInfo.logicOpEnable = this->upColorBlendState->logicOpEnable;
            colorBlendStateCreateInfo.logicOp = this->upColorBlendState->logicOp;
            colorBlendStateCreateInfo.attachmentCount = static_cast<uint32_t>(this->upColorBlendState->attachments.size());
            colorBlendStateCreateInfo.pAttachments = this->upColorBlendState->attachments.data();
            colorBlendStateCreateInfo.blendConstants[0] = this->upColorBlendState->blendConstants[0];
            colorBlendStateCreateInfo.blendConstants[1] = this->upColorBlendState->blendConstants[1];
            colorBlendStateCreateInfo.blendConstants[2] = this->upColorBlendState->blendConstants[2];
            colorBlendStateCreateInfo.blendConstants[3] = this->upColorBlendState->blendConstants[3];
        }

        VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
        dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        if (this->upDynamicState != nullptr) {
            dynamicStateCreateInfo.pNext = nullptr;
            dynamicStateCreateInfo.flags = 0;
            dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(this->upDynamicState->dynamicStates.size());
            dynamicStateCreateInfo.pDynamicStates = this->upDynamicState->dynamicStates.data();
        }

        return std::move(std::make_unique<GraphicsPipeline>(this->pLogicalDevice, this->flags, this->shaderStages, std::move(this->pushConstants),
                                                            this->pipelineCache, this->pBasePipeline, &inputAssemblyStateCreateInfo,
                                                            &vertexInputStateCreateInfo, &tessellationStateCreateInfo, viewPortStateCreateInfos,
                                                            &rasterizationStateCreateInfo, &multisampleStateCreateInfo, &depthStencilStateCreateInfo,
                                                            &colorBlendStateCreateInfo, &dynamicStateCreateInfo, this->pRenderPass, this->subpass));
    }
} // namespace fillcan