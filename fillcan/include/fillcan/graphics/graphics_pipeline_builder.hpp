#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/render_pass.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_builder.hpp>

// std
#include <array>
#include <memory>
#include <vector>

namespace fillcan {
    /**
     * Describe the input assembly state
     *
     * The input assembly stage reads the index and vertex buffers that contain information about the vertices
     * making up the draw sent in the draw command.
     *
     * @param topology The primitive topology.
     * @param primitiveRestartEnable Used to restart primitive topologies of type "strip" and "fan". Requires an indexed draw.
     */
    struct PipelineInputAssemblyState {
        VkPrimitiveTopology topology;
        VkBool32 primitiveRestartEnable;
    };

    /**
     * Describe the vertex input state
     *
     * The vertex input stage inputs vertex-data into the vertex shader.
     *
     * @param vertexInputBindingDescriptions Descriptions of the vertex-bindings.
     * @param vertexInputAttributeDescriptions Descriptions of the vertex-attributes.
     */
    struct PipelineVertexInputState {
        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
    };

    /**
     * Describe the tessellation control and evaluation stage
     *
     * The Tessellation control shader is responsible for producing tessellation factors and other pre-patch data.
     * that is used by the fixed-function tessellation engine.
     *
     * The tessellation evaluation shader runs on each new vertex produced by the tessellation primitive generator.
     * It operates similarly to a vertex shader except that incoming vertices are generated rather than read from memory.
     *
     * @param patchControlPoints The amount of controlpoints that will be grouped in a single primitive.
     */
    struct PipelineTessellationState {
        unsigned int patchControlPoints;
    };

    /**
     * Add a description of a viewport state.
     *
     * Viewport-transformation is the last coördinate transformation in the Graphics Pipeline before rasterization.
     * It transforms the normalized device-coördinates to window-coördinates.
     *
     * @param viewports The dimensions of each viewport.
     * @param scissors The scissor rectangles of each viewport.
     */
    struct PipelineViewPortState {
        std::vector<VkViewport> viewports;
        std::vector<VkRect2D> scissors;
    };

    /**
     * Describe the rasterization stage
     *
     * Rasterization is the fundamental core of all graphics in Vulkan.
     * The rasterizer takes assembled primitives that are still represented by a sequence of vertices
     * and turns them into individual fratments, which may become pixels that make up the output image.
     *
     * @param depthClampEnable Used to enable or disable depth clamping. This means that fragments that are outside the near and far planes are
     *                         clamped instead of thrown out. This requires the VkPipelineRasterizationDepthClipStateCreateInfoEXT extension.
     * @param rasterizerDiscardEnable Used to disable rasterization altogether. When this flag is set, the rasterizer will not run and no fragments
     *                                   will be produced.
     * @param polygonMode Can be used to have Vulkan automatically turn triangles into points or lines.
     * @param cullmode Controls what parts of the input will be discarded.
     * @param frontFace Which direction a triangle faces is determined by the winding order of its vertice - whether they go clockwise or
     *                  counterclockwise in the window space.
     * @param depthBiasEnable This feature allows fragments to be depth compensated for before the depth test. This can be used to avoid depth fights.
     * @param depthBiasConstantFactor A scalar factor that determines the constant depth value added to each clip.
     * @param depthBiasClamp The maximum (or minimum) depth bias of a fragment.
     * @param depthBiasSlopeFactor A scalar factor applied to the slope of a fragment in depth bias calculations.
     * @param lineWidth The width of line primitives, in pixels. This applies to all lines gridded with the pipeline.
     */
    struct PipelineRasterizationState {
        VkBool32 depthClampEnable = VK_FALSE;
        VkBool32 rasterizerDiscardEnable = VK_FALSE;
        VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
        VkCullModeFlags cullmode = VK_CULL_MODE_NONE;
        VkFrontFace frontFace = VK_FRONT_FACE_CLOCKWISE;
        VkBool32 depthBiasEnable = VK_FALSE;
        float depthBiasConstantFactor = 0.0f;
        float depthBiasClamp = 0.0f;
        float depthBiasSlopeFactor = 0.0f;
        float lineWidth = 1.0f;
    };

    /**
     * Describe the multisampling stage
     *
     * Multisampling is the process of generating multiple samples for each pixel in an image. It is used to counteract aliasing and can significantly
     * improve image quality when used effectively.
     *
     * @param multisampleState Structure containing the parameters for instancing the multisample state.
     */
    struct PipelineMultisampleState {
        VkSampleCountFlagBits rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        VkBool32 sampleShadingEnable = VK_FALSE;
        float minSampleShading = 1.0f;
        std::vector<VkSampleMask> sampleMask = {};
        VkBool32 alphaToCoverageEnable = VK_FALSE;
        VkBool32 alphaToOneEnable = VK_FALSE;
    };

    /**
     * Describe the depth- stencil state.
     *
     * The depth stencil state determines how the depth and stencil tests are performed and what happens to a snippet if it passes or fails one of
     * these tests.
     * The depth and stencil tests can be performed before or after the fragment shader has been run.
     * By default, the tests take place after the fragment shader.
     *
     * @param depthTestEnable Whether depth testing is enabled.
     * @param depthWriteEnable Whether depth writing is enabled. Depth writes are always disabled when depthTestEnable is VK_FALSE.
     * @param depthCompareOp The test to use.
     * @param depthBoundsTestEnable Whether Test Depth Limits is enabled.
     * @param stencilTestEnable Whether stencil testing is enabled.
     *                          If the depth test passes (or if the depth test is disabled), the snippet advances to the stencil test.
     * @param front Determines the parameters of the stencil test.
     * @param back Determines the parameters of the stencil test.
     * @param minDepthBounds The minimum depth limit used in the depth limit test.
     * @param maxDepthBounds The maximum depth limit used in the depth limit test.
     */
    struct PipelineDepthStencilState {
        VkBool32 depthTestEnable = VK_TRUE;
        VkBool32 depthWriteEnable = VK_TRUE;
        VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
        VkBool32 depthBoundsTestEnable = VK_FALSE;
        VkBool32 stencilTestEnable = VK_FALSE;
        VkStencilOpState front = {};
        VkStencilOpState back = {};
        float minDepthBounds = 0.0f;
        float maxDepthBounds = 1.0f;
    };

    /**
     * Describe the color blend stage
     *
     * The color operations take the final results of the fragment shader and postfragment operations and use them to update the framebuffer.
     * The color operations include blending and logic operations.
     * This stage is responsible for writing fragments in the color attachments.
     *
     * @param logicOpEnable Whether to perform logical operations between the fragment shader output and the contents of the color attachments.
     * @param logicOp The logical operation to apply.
     * @param attachments The color attachments to blend.
     * @param blendConstants A matrix of four values used as the R, G, B, and A components of the blending constant used in mixing, depending on the
     *                       mixing factor.
     */
    struct PipelineColorBlendState {
        VkBool32 logicOpEnable = VK_FALSE;
        VkLogicOp logicOp = VK_LOGIC_OP_COPY;
        std::vector<VkPipelineColorBlendAttachmentState> attachments = {};
        std::array<float, 4> blendConstants = {};
    };

    /**
     * Describe the dynamic state
     *
     * To make fine-grained state changes more manageable, Vulkan provides the ability to mark certain parts of the graphics pipeline as dynamic,
     * meaning they can be updated directly using commands directly in the command buffer rather than using an object. Since this reduces the chance
     * for Vulkan to optimize or absorb parts of the state, it is necessary to specify exactly which state to make dynamically.
     *
     * @param dynamicStates The states to make dynamic.
     */
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