<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void waitIdle();`} />
<MethodDescription>
    <span slot="details">
        Wait for the Logical Device to become idle.<br />
        Waits on the host for the completion of ongoing <Reference
            sectionID={SectionID.QUEUE}>Queue</Reference
        > operations for all
        <Reference sectionID={SectionID.QUEUE}>Queues</Reference> on this Logical
        Device.
    </span>
</MethodDescription>

<style lang="scss">
</style>
