#pragma once

// fillcan
#include "fillcan/instance/logical_device.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/memory/buffer.hpp>
#include <fillcan/shader/pipeline.hpp>

// std
#include <vector>

namespace fillcan {
    class RenderPass;

    class GraphicsPipeline : public Pipeline {
      private:
        RenderPass* pRenderPass;
        unsigned int subpass;
        std::vector<Buffer> vertexBuffers = {};

      public:
        GraphicsPipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags,
                         std::vector<PipelineShaderStage> shaderStages, VkPipelineCache pipelineCache, Pipeline* pBasePipeline,
                         VkPipelineVertexInputStateCreateInfo* pVertexInputState, VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState,
                         VkPipelineTessellationStateCreateInfo* pTessellationState, std::vector<VkPipelineViewportStateCreateInfo>& viewportState,
                         VkPipelineRasterizationStateCreateInfo* pRasterizationState, VkPipelineMultisampleStateCreateInfo* pMultisampleState,
                         VkPipelineDepthStencilStateCreateInfo* pDepthStencilState, VkPipelineColorBlendStateCreateInfo* pColorBlendState,
                         VkPipelineDynamicStateCreateInfo* pDynamicState, RenderPass* pRenderPass, unsigned int subpass);
        ~GraphicsPipeline();

        RenderPass* getRenderPass();

        void bindVertexBuffers(std::vector<Buffer>& vertexBuffers);

        void draw(unsigned int vertexCount, unsigned int instanceCount = 1, unsigned int firstVertex = 0, unsigned int firstInstance = 0);
    };
} // namespace fillcan