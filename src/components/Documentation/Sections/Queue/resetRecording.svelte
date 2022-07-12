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

        <br />
        <br />
        <span style="color: orange;">TODO:</span> Move to <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffer</Reference
        >.<br />
        Many applications use a similar set of commands to render all or part of
        each frame. Therefore, it is likely that similar <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
        > are included in the application over and over again.<br />
        Allocating and freeing <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        > (using <Reference sectionID={SectionID.QUEUE_freeRecording}
            >freeRecording</Reference
        >) every frame is a relatively heavy operation. If the application
        reuses a <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        > many times in a row for similar work, it may be more efficient to reset
        the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        >.<br />
        This effectively restores the <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffer</Reference
        > to its original state, but does not necessarily interact with the <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        > to do so. Therefore, if the <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffer</Reference
        > dynamically allocates resources from the <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        > as the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        > grows, the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        > can hold onto those resources and avoid the cost of reallocation the next
        time it is rebuilt.</span
    >
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
