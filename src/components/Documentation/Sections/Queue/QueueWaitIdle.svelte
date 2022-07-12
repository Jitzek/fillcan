<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool waitIdle();`} />
<MethodDescription>
    <span slot="details">
        Wait for the Queue to become idle.<br />
        When <code>waitIdle</code> returns <code>true</code>, all <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
        > sent to the Queue are guaranteed to be completed.
    </span>
    <span slot="return">
        <code>true</code> if the Queue was sucessfully waited on.
        <code>false</code> if something went wrong while waiting for the Queue to
        idle.
    </span>
</MethodDescription>

<style lang="scss">
</style>
