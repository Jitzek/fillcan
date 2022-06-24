#pragma once

// fillcan
#include "fillcan/instance/logical_device.hpp"
#include "fillcan/shader/pipeline_layout.hpp"
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
        std::vector<Buffer*> pVertexBuffers = {};
        Buffer* pIndexBuffer = nullptr;

      public:
        GraphicsPipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags,
                         std::vector<PipelineShaderStage> shaderStages, std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache,
                         Pipeline* pBasePipeline, VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState,
                         VkPipelineVertexInputStateCreateInfo* pVertexInputState, VkPipelineTessellationStateCreateInfo* pTessellationState,
                         std::vector<VkPipelineViewportStateCreateInfo>& viewportState, VkPipelineRasterizationStateCreateInfo* pRasterizationState,
                         VkPipelineMultisampleStateCreateInfo* pMultisampleState, VkPipelineDepthStencilStateCreateInfo* pDepthStencilState,
                         VkPipelineColorBlendStateCreateInfo* pColorBlendState, VkPipelineDynamicStateCreateInfo* pDynamicState,
                         RenderPass* pRenderPass, unsigned int subpass);
        ~GraphicsPipeline();

        RenderPass* getRenderPass();

        [[deprecated("Use models instead")]] void bindVertexBuffers(std::vector<Buffer*>& pVertexBuffers);

        [[deprecated("Use models instead")]] void bindIndexBuffer(Buffer* pIndexBuffer, VkIndexType indexType = VK_INDEX_TYPE_UINT16);

        [[deprecated("Use models instead")]] void draw(unsigned int vertexCount, unsigned int instanceCount = 1, unsigned int firstVertex = 0,
                                                       unsigned int firstInstance = 0);

        [[deprecated("Use models instead")]] void drawIndexed(unsigned int indexCount, unsigned int instanceCount = 1, unsigned int firstIndex = 0,
                                                              unsigned int vertexOffset = 0, unsigned int firstInstance = 0);

        void pushConstantData(std::string name, std::unique_ptr<PushConstantData> upPushConstantData);
        // PushConstant& getPushConstant(std::string name);
    };
} // namespace fillcan