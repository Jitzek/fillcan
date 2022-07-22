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
    code={`struct PipelineShaderStage {
    VkShaderStageFlagBits stage;
    ShaderModule* pShaderModule;
    std::string name;
    // TODO: Specialization Constants
};`}
/>

The <code>Pipeline Shader Stage</code> structure is used by the Pipeline to
construct the <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineShaderStageCreateInfo.html"
    target="_blank">VkPipelineShaderStageCreateInfo</Anchor
>-structure which is used by both the <Reference
    sectionID={SectionID.COMPUTE_PIPELINE}>compute pipeline</Reference
> and the <Reference sectionID={SectionID.GRAPHICS_PIPELINE}
    >graphics pipeline</Reference
>.<br />
<MethodDescription>
    <span slot="params">
        <li>
            <code>stage</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderStageFlagBits.html"
                target="_blank">VkShaderStageFlagBits</Anchor
            >-enumerant specifying the pipeline stage.
        </li>
        <li>
            <code>pShaderModule</code><br />
            A pointer to the <Reference sectionID={SectionID.SHADER_MODULE}
                >shader module</Reference
            > containing the shader code for this stage or nullptr.
        </li>
        <li>
            <code>name</code><br />
            The entry point name of the shader of this stage.
        </li>
    </span>
</MethodDescription>
