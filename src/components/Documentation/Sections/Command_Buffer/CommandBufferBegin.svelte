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
    code={`bool begin(
        VkCommandBufferUsageFlags flags = 0, 
        VkCommandBufferInheritanceInfo* pSecondaryCommandBufferInheritanceInfo = nullptr\n);`}
/>
<MethodDescription>
    <span slot="details"
        >Start the Command Buffer, which resets it to an initial state.</span
    >
    <div slot="params">
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferUsageFlagBits.html"
                target="_blank">VkCommandBufferUsageFlagBits</Anchor
            > telling Vulkan how the Command Buffer will be used.
        </li>
        <li>
            <code>pSecondaryCommandBufferInheritanceInfo</code><br />
            A <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferInheritanceInfo.html"
                target="_blank">VkCommandBufferInheritanceInfo</Anchor
            >-structure used when starting a secondary Command Buffer to define
            which states are inherited from the primary Command Buffer that
            calls it. For primary Command Buffers, this pointer is ignored.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the Command Buffer was succesfully started.
        <code>false</code> if the Command Buffer failed to start.
    </span>
</MethodDescription>

<style lang="scss">
</style>
