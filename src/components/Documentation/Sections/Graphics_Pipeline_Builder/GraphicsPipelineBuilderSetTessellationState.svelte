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
    code={`bool setVertexInputState(PipelineVertexInputState vertexInputState);`}
/>
<MethodDescription>
    <span slot="details">Set the Tessellation State.</span>
    <div slot="params">
        <li>
            <code>tessellationState</code><br />
            The tessellation state, this is a
            <code>PipelineTessellationState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineTessellationState {
    unsigned int patchControlPoints;
};`}
/>
<MethodDescription>
    <span slot="details">
        Describe the tessellation control and evaluation stage.<br />
        The Tessellation control shader is responsible for producing tessellation
        factors and other pre-patch data. that is used by the fixed-function tessellation
        engine. The tessellation evaluation shader runs on each new vertex produced
        by the tessellation primitive generator. It operates similarly to a vertex
        shader except that incoming vertices are generated rather than read from
        memory.
    </span>
    <div slot="params">
        <li>
            <code>patchControlPoints</code><br />
            The amount of controlpoints that will be grouped in a single primitive.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
