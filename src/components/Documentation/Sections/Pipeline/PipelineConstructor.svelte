<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`Pipeline(
    LogicalDevice* pLogicalDevice, 
    VkPipelineCreateFlags flags,
    std::vector<PipelineShaderStage> shaderStages, 
    std::vector<PushConstant> pushConstants,
    VkPipelineCache pipelineCache = VK_NULL_HANDLE, 
    Pipeline* pBasePipeline = nullptr\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Pipeline.<br />
        The <code>Pipeline</code> class is meant to be extended as it only contains
        the generic information and functionality shared by all pipelines.
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
            to switch/bind between .
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayout.html"
            target="_blank">Vulkan Pipeline Layout</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
