#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <array>
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_builder.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    struct PipelineInputAssemblyState {
        VkPrimitiveTopology topology;
        VkBool32 primitiveRestartEnable;
    };

    struct PipelineVertexInputState {
        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
    };

    struct PipelineTessellationState {
        unsigned int patchControlPoints;
    };

    struct PipelineViewPortState {
        std::vector<VkViewport> viewports;
        std::vector<VkRect2D> scissors;
    };

    struct PipelineRasterizationState {
        VkBool32 depthClampEnable = VK_FALSE;
        VkBool32 rasterizerDiscardEnable = VK_FALSE;
        VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
        VkCullModeFlags cullmode = VK_CULL_MODE_BACK_BIT;
        VkFrontFace frontFace = VK_FRONT_FACE_CLOCKWISE;
        VkBool32 depthBiasEnable = VK_FALSE;
        float depthBiasConstantFactor = 0.0f;
        float depthBiasClamp = 0.0f;
        float depthBiasSlopeFactor = 0.0f;
        float lineWidth = 1.0f;
    };

    struct PipelineMultisampleState {
        VkSampleCountFlagBits rasterizationSamples;
        VkBool32 sampleShadingEnable;
        float minSampleShading;
        std::vector<VkSampleMask> sampleMask;
        VkBool32 alphaToCoverageEnable;
        VkBool32 alphaToOneEnable;
    };

    struct PipelineDepthStencilState {
        VkBool32 depthTestEnable;
        VkBool32 depthWriteEnable;
        VkCompareOp depthCompareOp;
        VkBool32 depthBoundsTestEnable;
        VkBool32 stencilTestEnable;
        VkStencilOpState front;
        VkStencilOpState back;
        float minDepthBounds;
        float maxDepthBounds;
    };

    struct PipelineColorBlendState {
        VkBool32 logicOpEnable;
        VkLogicOp logicOp;
        std::vector<VkPipelineColorBlendAttachmentState> attachments;
        std::array<float, 4> blendConstants;
    };

    struct PipelineDynamicState {
        std::vector<VkDynamicState> dynamicStates;
    };

    class GraphicsPipelineBuilder : public PipelineBuilder {
      private:
        std::vector<PipelineShaderStage> shaderStages = {};
        std::unique_ptr<PipelineVertexInputState> upVertexInputState = nullptr;
        std::unique_ptr<PipelineInputAssemblyState> upInputAssemblyState = nullptr;
        std::unique_ptr<PipelineTessellationState> upTessellationState = nullptr;
        std::vector<std::unique_ptr<PipelineViewPortState>> upViewPortStates = {};
        std::unique_ptr<PipelineRasterizationState> upRasterizationState = nullptr;
        std::unique_ptr<PipelineMultisampleState> upMultisampleState = nullptr;
        std::unique_ptr<PipelineDepthStencilState> upDepthStencilState = nullptr;
        std::unique_ptr<PipelineColorBlendState> upColorBlendState = nullptr;
        std::unique_ptr<PipelineDynamicState> upDynamicState = nullptr;
        RenderPass* pRenderPass = nullptr;
        unsigned int subpass = 0;

      public:
        GraphicsPipelineBuilder();
        ~GraphicsPipelineBuilder();

        void addShaderStage(PipelineShaderStage shaderStage);
        void setInputAssemblyState(PipelineInputAssemblyState inputAssemblyState);
        bool setVertexInputState(PipelineVertexInputState vertexInputState);
        void setTessellationState(PipelineTessellationState tessellationState);
        bool addViewportState(PipelineViewPortState viewportState);
        bool setRasterizationState(PipelineRasterizationState rasterizationState);
        void setMultisampleState(PipelineMultisampleState multisampleState);
        void setDepthStencilState(PipelineDepthStencilState depthStencilState);
        void setColorBlendState(PipelineColorBlendState colorBlendState);
        void setDynamicState(PipelineDynamicState dynamicState);
        void setRenderPass(RenderPass* pRenderPass);
        void setSubpass(unsigned int subpass);

        void reset() override;
        std::unique_ptr<GraphicsPipeline> getResult();
    };
} // namespace fillcan