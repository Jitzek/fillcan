<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool shouldClose();`} />
<MethodDescription>
    <span slot="details">
        Whether the Window should close, e.g. the user attempts to close it.
    </span>
    <span slot="return">
        <code>true</code> if the Window should close. <code>false</code> if the Window shouldn't close.
    </span>
</MethodDescription>

<style lang="scss">
</style>
