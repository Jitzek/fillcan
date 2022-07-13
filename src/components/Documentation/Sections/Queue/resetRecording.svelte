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
    code={`bool resetRecording(CommandRecording* pCommandRecording, VkCommandBufferResetFlags flags);`}
/>
<MethodDescription>
    <span slot="details">
        Reset a <Reference sectionID={SectionID.COMMAND_RECORDING}
            >Command Recording</Reference
        >.<br />
        This will call <Reference sectionID={SectionID.COMMAND_BUFFER_reset}
            >reset</Reference
        > on every <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        > in the given <Reference sectionID={SectionID.COMMAND_RECORDING}
            >Command Recording</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>pCommandRecordings</code><br />
            The <Reference sectionID={SectionID.COMMAND_RECORDING}
                >Command Recordings</Reference
            > to reset.
        </li>
        <li>
            <code>flags</code><br />
            Additional actions to perform while resetting the <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffer</Reference
            >. This is a bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferResetFlagBits.html"
                target="_blank">VkCommandBufferResetFlagBits</Anchor
            >
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the Command Recording was succesfully reset.
        <code>false</code> if the Command Recording failed to reset.
    </span>
</MethodDescription>

<style lang="scss">
</style>
