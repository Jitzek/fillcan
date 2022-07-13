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
    code={`CommandBuffer(VkCommandBuffer hCommandBuffer, VkCommandBufferLevel level);`}
/>
<MethodDescription>
    <span slot="details">Create a new Command Buffer.</span>
    <div slot="params">
        <li>
            <code>hCommandBuffer</code><br />
            A handle to the <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBuffer.html"
                target="_blank">Vulkan Command Buffer</Anchor
            > to wrap.
        </li>
        <li>
            <code>level</code><br />
            The level at which the Command Buffer operates. This should be a member
            of the <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferLevel.html"
                target="_blank">VkCommandBufferLevel</Anchor
            >-enumerant.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
