<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void free();`} />
<MethodDescription>
    <span slot="details">
        Free this recording.<br />
        Calls <Reference sectionID={SectionID.QUEUE_freeRecording}
            >freeRecording</Reference
        > for this recording.
    </span>
</MethodDescription>

<style lang="scss">
</style>
