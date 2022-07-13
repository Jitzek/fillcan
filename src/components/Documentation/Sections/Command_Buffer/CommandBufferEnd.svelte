<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool end();`} />
<MethodDescription>
    <span slot="details"
        >End the Command Buffer.<br />
        Before the Command Buffer is ready to be sent to the device for execution,
        we need to tell Vulkan that we're done recording commands in it.</span
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
        <code>true</code> if the Command Buffer was succesfully ended.
        <code>false</code> if the Command Buffer failed to end.
    </span>
</MethodDescription>

<style lang="scss">
</style>
