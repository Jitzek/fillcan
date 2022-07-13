<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool submit();`} />
<MethodDescription>
    <span slot="details">
        Submit <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        > to the <Reference sectionID={SectionID.QUEUE}>Queue</Reference>.<br />
        alls <Reference sectionID={SectionID.QUEUE_submitRecordings}
            >submitRecordings</Reference
        > for this recording.
    </span>
    <span slot="return">
        <code>true</code> if the recording was succesfully submitted to the <Reference
            sectionID={SectionID.QUEUE}>Queue</Reference
        >.
        <code>false</code> if the recording failed to submit to the <Reference
            sectionID={SectionID.QUEUE}>Queue</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
