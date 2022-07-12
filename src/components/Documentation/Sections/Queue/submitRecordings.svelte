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
    code={`bool submitRecordings(std::vector<CommandRecording*> pCommandRecordings, Fence* pFence = nullptr);`}
/>
<MethodDescription>
    <span slot="details">
        Submit one or more <Reference sectionID={SectionID.COMMAND_RECORDING}
            >Command Recordings</Reference
        > to be executed by the Queue.
    </span>
    <div slot="params">
        <li>
            <code>pCommandRecordings</code><br />
            The <Reference sectionID={SectionID.COMMAND_RECORDING}
                >Command Recordings</Reference
            > to submit.
        </li>
        <li>
            <code>pFence</code><br />
            A pointer to a <Reference sectionID={SectionID.FENCE}
                >Fence</Reference
            > to signal once all submitted <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > have completed execution.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if all Command Recordings were succesfully submitted
        to the Queue. <code>false</code> if not all Command Recordings were succesfully
        submitted to the Queue.
    </span>
</MethodDescription>

<style lang="scss">
</style>
