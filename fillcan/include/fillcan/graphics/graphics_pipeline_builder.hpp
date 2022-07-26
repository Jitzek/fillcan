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
     * Describe the input assembly state.
     *
     * The input assembly stage reads the index and vertex buffers that contain information about the vertices
     * making up the draw sent in the draw command.
     *
     * @param topology The primitive topology. This is a member of the VkPrimitiveTopology-enumeration.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPrimitiveTopology.html
     * @param primitiveRestartEnable Used to restart primitive topologies of type "strip" and "fan". Requires an indexed draw.
     */
    struct PipelineInputAssemblyState {
        VkPrimitiveTopology topology;
        VkBool32 primitiveRestartEnable;
    };

    /**
     * Describe the vertex input state.
     *
     * The vertex input stage inputs vertex-data into the vertex shader.
     *
     * @param vertexInputBindingDescriptions Descriptions of the vertex-bindings. This is a list of VkVertexInputBindingDescription-structures.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkVertexInputBindingDescription.html
     * @param vertexInputAttributeDescriptions Descriptions of the vertex-attributes. This is a list of VkVertexInputAttributeDescription-structures.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkVertexInputAttributeDescription.html
     */
    struct PipelineVertexInputState {
        std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
    };

    /**
     * Describe the tessellation control and evaluation stage.
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
     * A description of a viewport state.
     *
     * Viewport-transformation is the last coördinate transformation in the Graphics Pipeline before rasterization.
     * It transforms the normalized device-coördinates to window-coördinates.
     *
     * @param viewports The dimensions of each viewport. This is a VkViewport-structure.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkViewport.html
     * @param scissors The scissor rectangles of each viewport. This is a VkRect2D-structure.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkRect2D.html
     */
    struct PipelineViewPortState {
        std::vector<VkViewport> viewports;
        std::vector<VkRect2D> scissors;
    };

    /**
     * Describe the rasterization stage.
     *
     * Rasterization is the fundamental core of all graphics in Vulkan.
     * The rasterizer takes assembled primitives that are still represented by a sequence of vertices
     * and turns them into individual fratments, which may become pixels that make up the output image.
     *
     * @param depthClampEnable Used to enable or disable depth clamping. This means that fragments that are outside the near and far planes are
     * clamped instead of thrown out. This requires the VkPipelineRasterizationDepthClipStateCreateInfoEXT extension.
     * @param rasterizerDiscardEnable Used to disable rasterization altogether. When this flag is set, the rasterizer will not run and no fragments
     * will be produced.
     * @param polygonMode Can be used to have Vulkan automatically turn triangles into points or lines. This a member of the
     * VkPolygonMode-enumeration.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPolygonMode.html
     * @param cullmode Controls what parts of the input will be discarded. This is a bitmask of VkCullModeFlagBits.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkCullModeFlagBits.html
     * @param frontFace Which direction a triangle faces is determined by the winding order of its vertice - whether they go clockwise or
     * counterclockwise in the window space. This is a member of the VkFrontFace-enumerant.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFrontFace.html
     * @param depthBiasEnable This feature allows fragments to be depth compensated for before the depth test. This can be used to avoid depth fights.
     * @param depthBiasConstantFactor A scalar factor that determines the constant depth value added to each clip.
     * @param depthBiasClamp The maximum (or minimum) depth bias of a fragment.
     * @param depthBiasSlopeFactor A scalar factor applied to the slope of a fragment in depth bias calculations.
     * @param lineWidth The width of line primitives, in pixels. This applies to all lines gridded with the pipeline.
     * Some Vulkan implementations do not support broad strokes and may ignore this field. Others can work very slowly if this field is not 1.0f;
     * still others can fully respect this field and discard all lines if lineWidth is set to 0.0f. Therefore, this field should always be set
     * to 1.0f, unless it is certain that it should be otherwise.
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
     * Describe the multisampling stage.
     *
     * Multisampling is the process of generating multiple samples for each pixel in an image. It is used to counteract aliasing and can significantly
     * improve image quality when used effectively.
     *
     * @param rasterizationSamples Not yet researched. This is a member of VkSampleCountFlagBits.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleCountFlagBits.html
     * @see
     * @param sampleShadingEnable Not yet researched.
     * @param minSampleShading Not yet researched. This is a list of VkSampleMask-structure.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleMask.html
     * @param sampleMask Not yet researched.
     * @param alphaToCoverageEnable Not yet researched.
     * @param alphaToCoverageEnable Not yet researched.
     * @param alphaToOneEnable Not yet researched.
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
     * @param depthCompareOp The test to use. This is a member of the VkComareOp-enumerant.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkComareOp.html
     * @param depthBoundsTestEnable Whether depth limits tests are enabled.
     * @param stencilTestEnable Whether stencil testing is enabled.
     * If the depth test passes (or if the depth test is disabled), the snippet advances to the stencil test.
     * @param front Determines the parameters of the stencil test. This is a member of the VkStencilOpState-enumerant.
     * @param back Determines the parameters of the stencil test. This is a member of the VkStencilOpState-enumerant.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkStencilOpState.html
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
     * Describe the color blend state.
     *
     * The color operations take the final results of the fragment shader and postfragment operations and use them to update the framebuffer.
     * The color operations include blending and logic operations.
     * This stage is responsible for writing fragments in the color attachments.
     *
     * @param logicOpEnable Whether to perform logical operations between the fragment shader output and the contents of the color attachments.
     * @param logicOp The logical operation to apply. This is a member of the VkLogicOp-enumerant.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkLogicOp.html
     * @param attachments The color attachments to blend. This is a list of VkPipelineColorBlendAttachmentState-structures.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineColorBlendAttachmentState.html
     * @param blendConstants A matrix of four values used as the R, G, B, and A components of the blending constant used in mixing, depending on the
     * mixing factor.
     */
    struct PipelineColorBlendState {
        VkBool32 logicOpEnable = VK_FALSE;
        VkLogicOp logicOp = VK_LOGIC_OP_COPY;
        std::vector<VkPipelineColorBlendAttachmentState> attachments = {};
        std::array<float, 4> blendConstants = {};
    };

    /**
     * Describe the dynamic state.
     *
     * To make fine-grained state changes more manageable, Vulkan provides the ability to mark certain parts of the graphics pipeline as dynamic,
     * meaning they can be updated directly using commands directly in the command buffer rather than using an object. Since this reduces the chance
     * for Vulkan to optimize or absorb parts of the state, it is necessary to specify exactly which state to make dynamically.
     *
     * @param dynamicStates The states to make dynamic. This is a list of VkDynamicState-structures.
     * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDynamicState.html
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

        /**
         * @brief Add a pipeline shader stage.
         *
         * @param shaderStage The pipeline shader stage to add.
         * @see Pipeline#PipelineShaderStage
         */
        void addShaderStage(PipelineShaderStage shaderStage);

        /**
         * @brief Set the Input Assembly State.
         *
         * @param inputAssemblyState The input assembly state, this is a PipelineInputAssemblyState-structure.
         */
        void setInputAssemblyState(PipelineInputAssemblyState inputAssemblyState);

        /**
         * @brief Set the Vertex Input State.
         *
         * @param vertexInputState The vertex input state, this is a PipelineVertexInputState-structure.
         */
        void setVertexInputState(PipelineVertexInputState vertexInputState);

        /**
         * @brief Set the Tessellation State.
         *
         * @param tessellationState The tessellation state, this is a PipelineTessellationState-structure.
         */
        void setTessellationState(PipelineTessellationState tessellationState);

        /**
         * @brief Add a Viewport State.
         *
         * @param viewportState The viewport state, this is a PipelineViewPortState-structure.
         */
        void addViewportState(PipelineViewPortState viewportState);

        /**
         * @brief Set the Rasterization State.
         *
         * @param rasterizationState The rasterization state, this is a PipelineRasterizationState-structure.
         */
        void setRasterizationState(PipelineRasterizationState rasterizationState);

        /**
         * @brief Set the Multisample State.
         *
         * @param multisampleState The multisample state, this is a PipelineMultisampleState-structure.
         */
        void setMultisampleState(PipelineMultisampleState multisampleState);

        /**
         * @brief Set the Depth Stencil State.
         *
         * @param depthStencilState The multisample state, this is a PipelineDepthStencilState-structure.
         */
        void setDepthStencilState(PipelineDepthStencilState depthStencilState);

        /**
         * @brief Set the Color Blend State.
         *
         * @param colorBlendState The color blend state, this is a PipelineColorBlendState-structure.
         */
        void setColorBlendState(PipelineColorBlendState colorBlendState);

        /**
         * @brief Set the Dynamic State.
         *
         * @param dynamicState The dynamic state, this is a PipelineDynamicState-structure.
         */
        void setDynamicState(PipelineDynamicState dynamicState);

        /**
         * @brief Set the Render Pass that describes the environment in which the pipeline will be used.
         *
         * @param pRenderPass A pointer to a render pass that describes the environment in which the pipeline will be used.
         */
        void setRenderPass(RenderPass* pRenderPass);

        /**
         * @brief Set the subpass in the render pass where this pipeline will be used.
         *
         * @param subpass The index of the subpass in the render pass where this pipeline will be used.
         */
        void setSubpass(unsigned int subpass);

        /**
         * @brief Get the resulting Graphics Pipeline.
         *
         * @return A unique pointer to the Graphics Pipeline, it's ownership will be moved.
         *
         * @throws std::runtime_error if the Graphics Pipeline couldn't be created.
         */
        std::unique_ptr<GraphicsPipeline> getResult();

        void reset() override;
    };
} // namespace fillcan