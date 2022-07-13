<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`const VkCommandBufferLevel getLevel() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get the level at which the Command Buffer operates.
    </span>
    <span slot="return">
        The level at which the Command Buffer operates. This is a member of the
        <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferLevel.html"
            target="_blank">VkCommandBufferLevel</Anchor
        >-enumerant.
    </span>
</MethodDescription>

<style lang="scss">
</style>
