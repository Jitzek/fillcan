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
    code={`const std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR() const;`}
/>
<MethodDescription>
    <span slot="details">
        Query the supported <Reference sectionID={SectionID.SWAPCHAIN}
            >Swapchain</Reference
        > format with colorspace pairs for the <Reference
            sectionID={SectionID.WINDOW}>Window</Reference
        > surface.
    </span>
    <span slot="return">
        A list of <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceFormatKHR.html"
            target="_blank">VkSurfaceFormatKHR</Anchor
        >-structures specifying the supported format with colorspace pairs for
        the <Reference sectionID={SectionID.WINDOW}>Window</Reference> surface.</span
    >
</MethodDescription>

<style lang="scss">
</style>
