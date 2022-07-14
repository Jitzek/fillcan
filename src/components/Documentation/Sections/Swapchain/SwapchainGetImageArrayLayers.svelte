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
    code={`unsigned int getImageArrayLayers();`}
/>
<MethodDescription>
    <span slot="details">
        Get the amount of array layers a Swapchain <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        > of this Swapchain supports.</span
    >
    <span slot="return">
        The amount of array layers a Swapchain <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        > of this Swapchain supports.
    </span>
</MethodDescription>

<style lang="scss">
</style>
