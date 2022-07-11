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
    code={`const VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR() const;`}
/>
<MethodDescription>
    <span slot="details">
        Query the basic capabilities of the <Reference
            sectionID={SectionID.WINDOW}>Window</Reference
        > surface, needed in order to create a <Reference
            sectionID={SectionID.SWAPCHAIN}>Swapchain</Reference
        >.
    </span>
    <span slot="return"
        >A <Anchor
            href="https://khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceCapabilitiesKHR.html"
            target="_blank">VkSurfaceCapabilitiesKHR</Anchor
        >-structure specifying the basic capabilities of the <Reference
            sectionID={SectionID.WINDOW}>Window</Reference
        > surface.</span
    >
</MethodDescription>

<style lang="scss">
</style>
