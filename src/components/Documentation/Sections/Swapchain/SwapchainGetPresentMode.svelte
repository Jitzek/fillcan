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
    code={`VkPresentModeKHR getPresentMode();`}
/>
<MethodDescription>
    <span slot="details">
        Get the current presentation mode for the surface of this Swapchain.</span
    >
    <span slot="return">
        A member of the <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html"
            target="_blank">VkPresentModeKHR</Anchor
        >-enumerant describing the current presentation mode of this Swapchain.
    </span>
</MethodDescription>

<style lang="scss">
</style>
