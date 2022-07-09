<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool wasResized();`} />
<MethodDescription>
    <span slot="details">
        Whether the Window was resized.
    </span>
    <span slot="return">
        <code>true</code> if the Window was resized. <code>false</code> if the Window wasn't resized.
    </span>
</MethodDescription>

<style lang="scss">
</style>
