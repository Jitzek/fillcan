<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void pollEvents();`} />
<MethodDescription>
    <span slot="details">
        Poll for events, e.g. close button pressed, window resized or other user
        interaction.
    </span>
</MethodDescription>

<style lang="scss">
</style>
