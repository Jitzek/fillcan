#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

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
        /**
         * @brief Create a new Graphics Pipeline.
         *
         * @details The Graphics Pipeline class extends the Pipeline class.
         * Creating a graphical pipeline is accomplished using a method similar to that of creating a compute pipeline. However, the graphics
         * pipeline contains many shader stages and fixed function processing blocks, so the description of a graphics pipeline is much more complex.
         *
         * The most basic rendering will contain at least a vertex and a fragment shader. Each shader stage can consume data from the previous stage
         * or pass data to the next, forming a pipeline. In some cases, the inputs to a shader are provided by fixed function blocks, and sometimes
         * the outputs of a shader are consumed by fixed function blocks. Regardless of the source or destination of data, the way to declare the
         * input and output to shaders is the same.
         *
         * @param pLogicalDevice A pointer to the Logical Device the pipeline should be associated with.
         * @param flags A bitmask of VkPipelineCreateFlagBits controlling how the pipeline is created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCreateFlags.html
         * @param shaderStages A list of PipelineShaderStage-structures each of which defining a shader stage of the pipeline.
         * @param pushConstants A list of push constants to be bound to the pipeline.
         * @param pipelineCache A handle to a Vulkan Pipeline Cache object.
         * Allows the result of pipeline construction to be reused between pipelines and between runs of an application. Reuse between pipelines is
         * achieved by passing the same pipeline cache object when creating multiple related pipelines. Reuse across runs of an application is
         * achieved by retrieving pipeline cache contents in one run of an application, saving the contents, and using them to preinitialize a
         * pipeline cache on a subsequent run.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html
         * @param pBasePipeline A pointer to the pipeline to derive from.
         * A pipeline derivative is a child pipeline created from a parent pipeline, where the child and parent pipeline are expected to have a lot of
         * commonality. The purpose of derived pipelines is that they can be made cheaper with the parent in mind, and that it is more efficient (on
         * host or device) to switch/bind between.
         * @param pInputAssemblyState A pointer to a VkPipelineInputAssemblyStateCreateInfo-structure describing the input assembly state.
         * The input assembly stage reads the index and vertex buffers that contain information about the vertices making up the draw sent in the draw
         * command.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineInputAssemblyStateCreateInfo.html
         * @param pVertexInputState A pointer to a VkPipelineVertexInputStateCreateInfo-structure describing the vertex input state.
         * The vertex input stage inputs vertex-data into the vertex shader.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineVertexInputStateCreateInfo.html
         * @param pTessellationState A pointer to a VkPipelineTessellationStateCreateInfo-structure describing the tessellation state.
         * The Tessellation control shader is responsible for producing tessellation factors and other pre-patch data. that is used by the
         * fixed-function tessellation engine. The tessellation evaluation shader runs on each new vertex produced by the tessellation primitive
         * generator. It operates similarly to a vertex shader except that incoming vertices are generated rather than read from memory.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineTessellationStateCreateInfo.html
         * @param viewportState A list of VkPipelineViewportStateCreateInfo-structures each of which describing a viewport state.
         * Viewport-transformation is the last coördinate transformation in the Graphics Pipeline before rasterization. It transforms the normalized
         * device-coördinates to window-coördinates.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineViewportStateCreateInfo.html
         * @param pRasterizationState A pointer to a VkPipelineRasterizationStateCreateInfo-structure describing the rasterization state.
         * Rasterization is the fundamental core of all graphics in Vulkan. The rasterizer takes assembled primitives that are still represented by a
         * sequence of vertices and turns them into individual fratments, which may become pixels that make up the output image.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineRasterizationStateCreateInfo.html
         * @param pMultisampleState A pointer to a VkPipelineMultisampleStateCreateInfo-structure describing the multisample state.
         * Multisampling is the process of generating multiple samples for each pixel in an image. It is used to counteract aliasing and can
         * significantly improve image quality when used effectively.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineMultisampleStateCreateInfo.html
         * @param pDepthStencilState A pointer to a VkPipelineDepthStencilStateCreateInfo-structure describing the depth- stencil state.
         * The depth stencil state determines how the depth and stencil tests are performed and what happens to a snippet if
         * it passes or fails one of these tests. The depth and stencil tests can be performed before or after the fragment shader has been run. By
         * default, the tests take place after the fragment shader.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineDepthStencilStateCreateInfo.html
         * @param pColorBlendState A pointer to a VkPipelineColorBlendStateCreateInfo-structure describing the color blend state.
         * The color operations take the final results of the fragment shader and postfragment operations and use them to update the framebuffer. The
         * color operations include blending and logic operations. This stage is responsible for writing fragments in the color attachments.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineColorBlendStateCreateInfo.html
         * @param pDynamicState A pointer to a VkPipelineDynamicStateCreateInfo-structure describing the dynamic state.
         * To make fine-grained state changes more manageable, Vulkan provides the ability to mark certain parts of the graphics
         * pipeline as dynamic, meaning they can be updated directly using commands directly in the command buffer rather than using an object. Since
         * this reduces the chance for Vulkan to optimize or absorb parts of the state, it is necessary to specify exactly which state to make
         * dynamically.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineDynamicStateCreateInfo.html
         * @param pRenderPass A pointer to a render pass that describes the environment in which the pipeline will be used.
         * @param subpass The index of the subpass in the render pass where this pipeline will be used.
         *
         * @throws std::runtime_error if the pipeline layout couldn't be created.
         * @throws std::runtime_error if the Vulkan Graphics Pipeline couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipeline.html
         *
         * @note It is recommended to not create a Compute Pipeline by it's Constructor, but to use a Compute Pipeline Builder instead.
         */
        GraphicsPipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                         std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache, Pipeline* pBasePipeline,
                         VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState, VkPipelineVertexInputStateCreateInfo* pVertexInputState,
                         VkPipelineTessellationStateCreateInfo* pTessellationState, std::vector<VkPipelineViewportStateCreateInfo>& viewportState,
                         VkPipelineRasterizationStateCreateInfo* pRasterizationState, VkPipelineMultisampleStateCreateInfo* pMultisampleState,
                         VkPipelineDepthStencilStateCreateInfo* pDepthStencilState, VkPipelineColorBlendStateCreateInfo* pColorBlendState,
                         VkPipelineDynamicStateCreateInfo* pDynamicState, RenderPass* pRenderPass, unsigned int subpass);
        ~GraphicsPipeline();
        GraphicsPipeline(const GraphicsPipeline&) = delete;
        GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;

        /**
         * @brief Get the Render Pass that describes the environment in which this pipeline is used.
         *
         * @return The render pass with which this pipeline associates.
         */
        RenderPass* getRenderPass();

        [[deprecated("Use models instead")]] void bindVertexBuffers(std::vector<Buffer*>& pVertexBuffers);

        [[deprecated("Use models instead")]] void bindIndexBuffer(Buffer* pIndexBuffer, VkIndexType indexType = VK_INDEX_TYPE_UINT16);

        [[deprecated("Use models instead")]] void draw(unsigned int vertexCount, unsigned int instanceCount = 1, unsigned int firstVertex = 0,
                                                       unsigned int firstInstance = 0);

        [[deprecated("Use models instead")]] void drawIndexed(unsigned int indexCount, unsigned int instanceCount = 1, unsigned int firstIndex = 0,
                                                              unsigned int vertexOffset = 0, unsigned int firstInstance = 0);
    };
} // namespace fillcan