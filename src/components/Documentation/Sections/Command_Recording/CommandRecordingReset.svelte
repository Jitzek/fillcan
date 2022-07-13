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
    code={`bool reset(VkCommandBufferResetFlags flags = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Resets the recording and resets all structure variables to their default
        values.<br />
        Calls <Reference sectionID={SectionID.QUEUE_resetRecording}
            >resetRecording</Reference
        > for this recording before resetting all structure variables to their default
        values.
    </span>
    <div slot="params">
        <li>
            <code>flags</code><br />
            Additional actions to perform while resetting the <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            >. This is a bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferResetFlagBits.html"
                target="_blank">VkCommandBufferResetFlagBits</Anchor
            >
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the recording was succesfully reset.
        <code>false</code> if the recording failed to reset.
    </span>
</MethodDescription>

<style lang="scss">
</style>
