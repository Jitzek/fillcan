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
    code={`Queue* getGraphicsQueue();`}
/>
<MethodDescription>
    <span slot="details">
        Get a pointer to the graphics <Reference sectionID={SectionID.QUEUE}
            >Queue</Reference
        >.
    </span>
    <span slot="return">
        A pointer to the graphics <Reference sectionID={SectionID.QUEUE}
            >Queue</Reference
        > or <code>nullptr</code> if no <Reference sectionID={SectionID.QUEUE}
            >Queue</Reference
        > was found.</span
    >
</MethodDescription>

<style lang="scss">
</style>
