<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`GraphicsPipeline(
    LogicalDevice* pLogicalDevice, 
    VkPipelineCreateFlags flags, 
    std::vector<PipelineShaderStage> shaderStages,
    std::vector<PushConstant> pushConstants, 
    VkPipelineCache pipelineCache, 
    Pipeline* pBasePipeline,
    VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState, 
    VkPipelineVertexInputStateCreateInfo* pVertexInputState,
    VkPipelineTessellationStateCreateInfo* pTessellationState, 
    std::vector<VkPipelineViewportStateCreateInfo>& viewportState,
    VkPipelineRasterizationStateCreateInfo* pRasterizationState, 
    VkPipelineMultisampleStateCreateInfo* pMultisampleState,
    VkPipelineDepthStencilStateCreateInfo* pDepthStencilState, 
    VkPipelineColorBlendStateCreateInfo* pColorBlendState,
    VkPipelineDynamicStateCreateInfo* pDynamicState, 
    RenderPass* pRenderPass, 
    unsigned int subpass
);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Graphics Pipeline.<br />
        It is recommended to not create a Graphics Pipeline by it's Constructor,
        but to use a <Reference sectionID={SectionID.GRAPHICS_PIPELINE_BUILDER}
            >Graphics Pipeline Builder</Reference
        > instead.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Pipeline should be associated with.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCreateFlagBits.html"
                target="_blank">VkPipelineCreateFlagBits</Anchor
            > controlling how the pipeline is created.
        </li>
        <li>
            <code>shaderStages</code><br />
            A list of <Reference
                sectionID={SectionID.PIPELINE_PIPELINE_SHADER_STAGE}
                >PipelineShaderStage</Reference
            >-structures each of which defining a shader stage of the pipeline.
        </li>
        <li>
            <code>pushConstants</code><br />
            A list of <Reference
                sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
                >push constants</Reference
            > to be bound to the pipeline.
        </li>
        <li>
            <code>pipelineCache</code><br />
            A handle to a <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html"
                target="_blank">Vulkan Pipeline Cache</Anchor
            > object.<br />
            Allows the result of pipeline construction to be reused between pipelines
            and between runs of an application. Reuse between pipelines is achieved
            by passing the same pipeline cache object when creating multiple related
            pipelines. Reuse across runs of an application is achieved by retrieving
            pipeline cache contents in one run of an application, saving the contents,
            and using them to preinitialize a pipeline cache on a subsequent run.
        </li>
        <li>
            <code>pBasePipeline</code><br />
            A pointer to the pipeline to derive from.<br />
            A pipeline derivative is a child pipeline created from a parent pipeline,
            where the child and parent pipeline are expected to have a lot of commonality.
            The purpose of derived pipelines is that they can be made cheaper with
            the parent in mind, and that it is more efficient (on host or device)
            to switch/bind between.
        </li>
        <li>
            <code>pInputAssemblyState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineInputAssemblyStateCreateInfo"
                version={1.3}
                >VkPipelineInputAssemblyStateCreateInfo</VkReference
            >-structure describing the input assembly state. The input assembly
            stage reads the index and vertex buffers that contain information
            about the vertices making up the draw sent in the draw command.
        </li>
        <li>
            <code>pVertexInputState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineVertexInputStateCreateInfo"
                version={1.3}>VkPipelineVertexInputStateCreateInfo</VkReference
            >-structure describing the vertex input state. The vertex input
            stage inputs vertex-data into the vertex shader.
        </li>
        <li>
            <code>pTessellationState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineTessellationStateCreateInfo"
                version={1.3}>VkPipelineTessellationStateCreateInfo</VkReference
            >-structure describing the tessellation state. The Tessellation
            control shader is responsible for producing tessellation factors and
            other pre-patch data. that is used by the fixed-function
            tessellation engine. The tessellation evaluation shader runs on each
            new vertex produced by the tessellation primitive generator. It
            operates similarly to a vertex shader except that incoming vertices
            are generated rather than read from memory.
        </li>
        <li>
            <code>viewportState</code><br />
            A list of <VkReference
                reference="VkPipelineViewportStateCreateInfo"
                version={1.3}>VkPipelineViewportStateCreateInfo</VkReference
            >-structures each of which describing a viewport state.
            Viewport-transformation is the last coördinate transformation in the
            Graphics Pipeline before rasterization. It transforms the normalized
            device-coördinates to window-coördinates.
        </li>
        <li>
            <code>pRasterizationState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineRasterizationStateCreateInfo"
                version={1.3}
                >VkPipelineRasterizationStateCreateInfo</VkReference
            >-structure describing the rasterization state. Rasterization is the
            fundamental core of all graphics in Vulkan. The rasterizer takes
            assembled primitives that are still represented by a sequence of
            vertices and turns them into individual fratments, which may become
            pixels that make up the output image.
        </li>
        <li>
            <code>pMultisampleState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineMultisampleStateCreateInfo"
                version={1.3}>VkPipelineMultisampleStateCreateInfo</VkReference
            >-structure describing the multisample state. Multisampling is the
            process of generating multiple samples for each pixel in an image.
            It is used to counteract aliasing and can significantly improve
            image quality when used effectively.
        </li>
        <li>
            <code>pDepthStencilState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineDepthStencilStateCreateInfo"
                version={1.3}>VkPipelineDepthStencilStateCreateInfo</VkReference
            >-structure describing the depth- stencil state. The depth stencil
            state determines how the depth and stencil tests are performed and
            what happens to a snippet if it passes or fails one of these tests.
            The depth and stencil tests can be performed before or after the
            fragment shader has been run. By default, the tests take place after
            the fragment shader.
        </li>
        <li>
            <code>pColorBlendState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineColorBlendStateCreateInfo"
                version={1.3}>VkPipelineColorBlendStateCreateInfo</VkReference
            >-structure describing the color blend state. The color operations
            take the final results of the fragment shader and postfragment
            operations and use them to update the <Reference
                sectionID={SectionID.FRAMEBUFFER}>framebuffer</Reference
            >. The color operations include blending and logic operations. This
            stage is responsible for writing fragments in the color attachments.
        </li>
        <li>
            <code>pDynamicState</code><br />
            A pointer to a <VkReference
                reference="VkPipelineDynamicStateCreateInfo"
                version={1.3}>VkPipelineDynamicStateCreateInfo</VkReference
            >-structure describing the dynamic state. To make fine-grained state
            changes more manageable, Vulkan provides the ability to mark certain
            parts of the graphics pipeline as dynamic, meaning they can be
            updated directly using commands directly in the command buffer
            rather than using an object. Since this reduces the chance for
            Vulkan to optimize or absorb parts of the state, it is necessary to
            specify exactly which state to make dynamically.
        </li>
        <li>
            <code>pRenderPass</code><br />
            A pointer to a <Reference sectionID={SectionID.RENDER_PASS}
                >render pass</Reference
            > that describes the environment in which the pipeline will be used.
        </li>
        <li>
            <code>subpass</code><br />
            The index of the subpass in the <Reference
                sectionID={SectionID.RENDER_PASS}>render pass</Reference
            > where this pipeline will be used.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayout.html"
            target="_blank">Vulkan Pipeline Layout</Anchor
        > couldn't be created.<br />
        Also throws std::runtime_error if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipeline.html"
            target="_blank">Vulkan Compute Pipeline</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
