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
    code={`VkImageUsageFlags getImageUsage();`}
/>
<MethodDescription>
    <span slot="details">
        Get the supported usage for a Swapchain <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        > of this Swapchain.</span
    >
    <span slot="return">
        A bitmap of <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkImageUsageFlagBits.html"
            target="_blank">VkImageUsageFlagBits</Anchor
        > describing the supported usage for a Swapchain <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        > of this Swapchain.
    </span>
</MethodDescription>

<style lang="scss">
</style>
