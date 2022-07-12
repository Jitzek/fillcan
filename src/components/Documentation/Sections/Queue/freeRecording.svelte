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
    code={`void freeRecording(CommandRecording* pCommandRecording);`}
/>
<MethodDescription>
    <span slot="details">
        Free a <Reference sectionID={SectionID.COMMAND_RECORDING}
            >Command Recording</Reference
        >.<br />
        This will call <Reference
            sectionID={SectionID.COMMAND_POOL_freeCommandBuffers}
            >freeCommandBuffers</Reference
        > on the <Reference sectionID={SectionID.COMMAND_POOL}
            >Command Pool</Reference
        > for all the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        > in the given <Reference sectionID={SectionID.COMMAND_RECORDING}
            >Command Recording</Reference
        >.

        <br />
        <br />
        <span style="color: orange;">TODO:</span> Move to <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        >.<br />
        Freeing a <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        > does not necessarily free all its resources, but returns them to the <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        > from which they were allocated.
    </span>
    <div slot="params">
        <li>
            <code>pCommandRecording</code><br />
            The <Reference sectionID={SectionID.COMMAND_RECORDING}
                >Command Recording</Reference
            > to free.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
