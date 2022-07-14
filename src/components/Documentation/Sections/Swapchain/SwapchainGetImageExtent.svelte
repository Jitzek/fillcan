<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`VkExtent2D getImageExtent();`} />
<MethodDescription>
    <span slot="details">
        Get the extent (the width and height) of the Swapchain <Reference
            sectionID={SectionID.IMAGE}>Images</Reference
        > of this Swapchain.</span
    >
    <span slot="return">
        A <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkExtent2D.html"
            target="_blank">VkExtent2D</Anchor
        >-structure describing the width and height of the Swapchain
        <Reference sectionID={SectionID.IMAGE}>Images</Reference> of this Swapchain.
    </span>
</MethodDescription>

<style lang="scss">
</style>
