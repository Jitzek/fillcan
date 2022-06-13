#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_builder.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    // Seperate struct since the VkPipelineMultisampleStateCreateInfo-structure requires a pointer to a VkSampleMask
    // Which could result in the pointer being deleted before the Graphics Pipeline can be constructed.
    // This struct stores a copy of the VkSampleMask to prevent a loss of data.
    struct PipelineMultisampleState {
        VkSampleCountFlagBits rasterizationSamples;
        VkBool32 sampleShadingEnable;
        float minSampleShading;
        VkSampleMask sampleMask;
        VkBool32 alphaToCoverageEnable;
        VkBool32 alphaToOneEnable;
    };

    class GraphicsPipelineBuilder : public PipelineBuilder {
      private:
        std::vector<PipelineShaderStage> shaderStages = {};
        std::unique_ptr<VkPipelineVertexInputStateCreateInfo> upVertexInputState = nullptr;
        std::unique_ptr<VkPipelineInputAssemblyStateCreateInfo> upInputAssemblyState = nullptr;
        std::unique_ptr<VkPipelineTessellationStateCreateInfo> upTessellationState = nullptr;
        std::vector<VkPipelineViewportStateCreateInfo> viewportState = {};
        std::unique_ptr<VkPipelineRasterizationStateCreateInfo> upRasterizationState = nullptr;
        std::unique_ptr<PipelineMultisampleState> upMultisampleState = nullptr;
        std::unique_ptr<VkPipelineDepthStencilStateCreateInfo> upDepthStencilState = nullptr;
        std::unique_ptr<VkPipelineColorBlendStateCreateInfo> upColorBlendState = nullptr;
        std::unique_ptr<VkPipelineDynamicStateCreateInfo> upDynamicState = nullptr;
        RenderPass* pRenderPass = nullptr;
        unsigned int subpass = 0;

      public:
        GraphicsPipelineBuilder();
        ~GraphicsPipelineBuilder();

        void addShaderStage(PipelineShaderStage shaderStage);
        void setInputAssemblyState(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable);
        bool setVertexInputState(std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions,
                                 std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions);
        void setTessellationState(unsigned int patchControlPoints);
        bool addViewportState(std::vector<VkViewport> viewports, std::vector<VkRect2D> scissors);
        bool setRasterizationState(VkBool32 depthClampEnable = VK_FALSE, VkBool32 rasterizerDiscardEnable = VK_FALSE,
                                   VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL, VkCullModeFlags cullmode = VK_CULL_MODE_BACK_BIT,
                                   VkFrontFace frontFace = VK_FRONT_FACE_CLOCKWISE, VkBool32 depthBiasEnable = VK_FALSE,
                                   float depthBiasConstantFactor = 0.0f, float depthBiasClamp = 0.0f, float depthBiasSlopeFactor = 0.0f,
                                   float lineWidth = 1.0f);
        void setMultisampleState(PipelineMultisampleState multisampleState);
        void setDepthStencilState(VkBool32 depthTestEnable, VkBool32 depthWriteEnable, VkCompareOp depthCompareOp, VkBool32 depthBoundsTestEnable,
                                  VkBool32 stencilTestEnable, VkStencilOpState front, VkStencilOpState back, float minDepthBounds,
                                  float maxDepthBounds);
        void setColorBlendState(VkBool32 logicOpEnable, VkLogicOp logicOp, std::vector<VkPipelineColorBlendAttachmentState> attachments,
                                float blendConstants[4]);
        void setDynamicState(std::vector<VkDynamicState> dynamicStates);
        void setRenderPass(RenderPass* pRenderPass);
        void setSubpass(unsigned int subpass);

        void reset() override;
        std::unique_ptr<GraphicsPipeline> getResult();
    };
} // namespace fillcan