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
    code={`void addViewportState(PipelineViewPortState viewportState);`}
/>
<MethodDescription>
    <span slot="details">Add a Viewport State.</span>
    <div slot="params">
        <li>
            <code>viewportState</code><br />
            The viewport state, this is a
            <code>PipelineViewPortState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineViewPortState {
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
};`}
/>
<MethodDescription>
    <span slot="details">
        A description of a viewport state.<br />
        Viewport-transformation is the last coördinate transformation in the <Reference
            sectionID={SectionID.GRAPHICS_PIPELINE}>Graphics Pipeline</Reference
        > before rasterization. It transforms the normalized device-coördinates to
        window-coördinates.
    </span>
    <div slot="params">
        <li>
            <code>viewports</code><br />
            The dimensions of each viewport. This is a <VkReference
                reference="VkViewport"
                version={1.3}>VkViewport</VkReference
            >-structure.
        </li>
        <li>
            <code>scissors</code><br />
            The scissor rectangles of each viewport. This is a <VkReference
                reference="VkRect2D"
                version={1.3}>VkRect2D</VkReference
            >-structure.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
