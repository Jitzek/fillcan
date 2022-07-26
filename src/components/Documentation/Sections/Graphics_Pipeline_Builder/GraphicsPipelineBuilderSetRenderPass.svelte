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
    code={`void setRenderPass(RenderPass* pRenderPass);`}
/>
<MethodDescription>
    <span slot="details"
        >Set the <Reference sectionID={SectionID.RENDER_PASS}
            >Render Pass</Reference
        > that describes the environment in which the pipeline will be used.</span
    >
    <div slot="params">
        <li>
            <code>pRenderPass</code><br />
            A pointer to a render pass that describes the environment in which the
            pipeline will be used.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
