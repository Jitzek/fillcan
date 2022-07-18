<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool reset();`} />
<MethodDescription>
    <span slot="details">Reset the Fence to an unsignaled state.</span>
    <span slot="return">
        <code>true</code> if all the Fence was succesfully reset.
        <code>false</code> if the Fence failed to reset.
    </span>
</MethodDescription>

<style lang="scss">
</style>
