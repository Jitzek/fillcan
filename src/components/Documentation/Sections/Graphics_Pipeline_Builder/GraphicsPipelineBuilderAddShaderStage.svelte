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
    code={`void setShaderStage(PipelineShaderStage pipelineShaderStage);`}
/>
<MethodDescription>
    <span slot="details">
        Add a <Reference sectionID={SectionID.PIPELINE_PIPELINE_SHADER_STAGE}
            >pipeline shader stage</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>pipelineShaderStage</code><br />
            The <Reference sectionID={SectionID.PIPELINE_PIPELINE_SHADER_STAGE}
                >pipeline shader stage</Reference
            > to add.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
