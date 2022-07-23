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
    code={`void setPipelineCache(VkPipelineCache pipelineCache);`}
/>
<MethodDescription>
    <span slot="details"> Set the base pipeline for the pipeline. </span>
    <div slot="params">
        <li>
            <code>pBasePipeline</code><br />
            A pointer to the <Reference sectionID={SectionID.PIPELINE}
                >pipeline</Reference
            > to derive from.<br />
            A pipeline derivative is a child pipeline created from a parent pipeline,
            where the child and parent pipeline are expected to have a lot of commonality.
            The purpose of derived pipelines is that they can be made cheaper with
            the parent in mind, and that it is more efficient (on host or device)
            to switch/bind between.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
