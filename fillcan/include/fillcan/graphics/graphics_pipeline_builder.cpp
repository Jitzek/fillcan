// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/graphics/graphics_pipeline.hpp"
#include "fillcan/shader/pipeline_builder.hpp"
#include <fillcan/graphics/graphics_pipeline_builder.hpp>

// std
#include <array>
#include <memory>
#include <vector>

namespace fillcan {
    GraphicsPipelineBuilder::GraphicsPipelineBuilder() {}
    GraphicsPipelineBuilder::~GraphicsPipelineBuilder() {}

    void GraphicsPipelineBuilder::addShaderStage(PipelineShaderStage pipelineShaderStage) { this->shaderStages.push_back(pipelineShaderStage); }

    /**
     * Describe the input assembly state
     *
     * The input assembly stage reads the index and vertex buffers that contain information about the vertices
     * making up the draw sent in the draw command.
     *
     * @param topology The primitive topology.
     * @param primitiveRestartEnable Used to restart primitive topologies of type "strip" and "fan". Requires an indexed draw.
     * @return void
     */
    void GraphicsPipelineBuilder::setInputAssemblyState(PipelineInputAssemblyState inputAssemblyState) {
        this->upInputAssemblyState = std::make_unique<PipelineInputAssemblyState>(inputAssemblyState);
    }

    /**
     * Describe the vertex input state
     *
     * The vertex input stage inputs vertex-data into the vertex shader.
     *
     * @param vertexInputBindingDescriptions Descriptions of the vertex-bindings.
     * @param vertexInputAttributeDescriptions Descriptions of the vertex-attributes.
     * @return Whether the descriptions are supported by the device.
     */
    bool GraphicsPipelineBuilder::setVertexInputState(PipelineVertexInputState vertexInputState) {
        // TODO: Check whether the descriptions are supported by the device.
        this->upVertexInputState = std::make_unique<PipelineVertexInputState>(vertexInputState);
        return true;
    }

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
     * @return void
     */
    void GraphicsPipelineBuilder::setTessellationState(PipelineTessellationState tessellationState) {
        this->upTessellationState = std::make_unique<PipelineTessellationState>(tessellationState);
    }

    /**
     * Add a description of a viewport state.
     *
     * Viewport-transformation is the last coördinate transformation in the Graphics Pipeline before rasterization.
     * It transforms the normalized device-coördinates to window-coördinates.
     *
     * @param viewports The dimensions of each viewport.
     * @param scissors The scissor rectangles of each viewport.
     * @return Whether the viewports are supported by the device.
     */
    bool GraphicsPipelineBuilder::addViewportState(PipelineViewPortState viewportState) {
        // TODO: Check whether the amount of viewports is supported by the device
        this->upViewPortStates.push_back(std::move(std::make_unique<PipelineViewPortState>(viewportState)));
        return true;
    }

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
     * @return Whether the given parameters are supported by the device.
     */
    bool GraphicsPipelineBuilder::setRasterizationState(PipelineRasterizationState rasterizationState) {
        // TODO: Check whether the parameters are supported by the device
        this->upRasterizationState = std::make_unique<PipelineRasterizationState>(rasterizationState);
        return true;
    }

    /**
     * Describe the multisampling stage
     *
     * Multisampling is the process of generating multiple samples for each pixel in an image. It is used to counteract aliasing and can significantly
     * improve image quality when used effectively.
     *
     * @param multisampleState Structure containing the parameters for instancing the multisample state.
     * @return void
     */
    void GraphicsPipelineBuilder::setMultisampleState(PipelineMultisampleState multisampleState) {
        this->upMultisampleState = std::make_unique<PipelineMultisampleState>(multisampleState);
    }

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
     * @return void
     */
    void GraphicsPipelineBuilder::setDepthStencilState(PipelineDepthStencilState depthStencilState) {
        this->upDepthStencilState = std::make_unique<PipelineDepthStencilState>(depthStencilState);
    }

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
     * @return void
     */
    void GraphicsPipelineBuilder::setColorBlendState(PipelineColorBlendState colorBlendState) {
        this->upColorBlendState = std::make_unique<PipelineColorBlendState>(colorBlendState);
    }

    /**
     * Describe the dynamic state
     *
     * To make fine-grained state changes more manageable, Vulkan provides the ability to mark certain parts of the graphics pipeline as dynamic,
     * meaning they can be updated directly using commands directly in the command buffer rather than using an object. Since this reduces the chance
     * for Vulkan to optimize or absorb parts of the state, it is necessary to specify exactly which state to make dynamically.
     *
     * @param dynamicStates The states to make dynamic.
     * @return void
     */
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

        return std::move(std::make_unique<GraphicsPipeline>(
            this->pLogicalDevice, this->pCommandBuffer, this->flags, this->shaderStages, std::move(this->pushConstants), this->pipelineCache,
            this->pBasePipeline, &inputAssemblyStateCreateInfo, &vertexInputStateCreateInfo, &tessellationStateCreateInfo, viewPortStateCreateInfos,
            &rasterizationStateCreateInfo, &multisampleStateCreateInfo, &depthStencilStateCreateInfo, &colorBlendStateCreateInfo,
            &dynamicStateCreateInfo, this->pRenderPass, this->subpass));
    }
} // namespace fillcan