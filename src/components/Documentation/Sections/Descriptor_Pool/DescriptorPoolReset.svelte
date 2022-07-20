<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool reset();`} />
<MethodDescription>
    <span slot="details">Reset the descriptor pool.</span>
    <span slot="return">
        <code>true</code> if the descriptor pool was succesfully reset.
        <code>false</code> if the descriptor pool failed to reset. >
    </span></MethodDescription
>

<style lang="scss">
</style>
