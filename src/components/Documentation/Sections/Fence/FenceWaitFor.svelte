<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`bool waitFor(uint64_t timeout = UINT64_MAX);`}
/>
<MethodDescription>
    <span slot="details"> Wait for the Fence to be signaled.</span>
    <div slot="params">
        <li>
            <code>timeout</code><br />
            The timeout period in units of nanoseconds to wait before returning.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the Fence was succesfully waited for.
        <code>false</code> if the timeout expired.
    </span>
</MethodDescription>

<style lang="scss">
</style>
