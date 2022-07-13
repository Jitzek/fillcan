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
    code={`void waitForFence(uint64_t timeout = UINT64_MAX);`}
/>
<MethodDescription>
    <span slot="details">
        Wait for the <Reference sectionID={SectionID.FENCE}>Fence</Reference> defined
        with <Reference sectionID={SectionID.COMMAND_RECORDING_createFence}
            >createFence</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>timeout</code><br />
            The timeout period in units of nanoseconds to wait before returning.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
