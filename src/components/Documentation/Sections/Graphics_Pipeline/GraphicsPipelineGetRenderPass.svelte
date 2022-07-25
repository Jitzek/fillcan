<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`RenderPass* getRenderPass();`} />
<MethodDescription>
    <span slot="details">
        Get the <Reference sectionID={SectionID.RENDER_PASS}
            >render pass</Reference
        > that describes the environment in which this pipeline is used.
    </span>
    <span slot="return">
        The <Reference sectionID={SectionID.RENDER_PASS}>render pass</Reference>
        with which this pipeline associates.
    </span>
</MethodDescription>

<style lang="scss">
</style>
