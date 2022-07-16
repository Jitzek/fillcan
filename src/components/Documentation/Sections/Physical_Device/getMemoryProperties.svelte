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
    code={`const VkFormatProperties getFormatProperties(VkFormat format) const;`}
/>
<MethodDescription>
    <span slot="details">
        Query the memory properties of this Physical Device.
    </span>
    <span slot="return">
        A <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceMemoryProperties.html"
            target="_blank">VkPhysicalDeviceMemoryProperties</Anchor
        >-structure specifying the memory properties of this Physical Device.
    </span>
</MethodDescription>

<style lang="scss">
</style>
