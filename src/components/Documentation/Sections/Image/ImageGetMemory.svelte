<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`Memory* getMemory() const;`} />
<MethodDescription>
    <span slot="details"
        >Get the Memory bound with <Reference
            sectionID={SectionID.BUFFER_bindMemory}>bindMemory</Reference
        >.</span
    >
    <span slot="return">
        A pointer to the bound <Reference sectionID={SectionID.MEMORY}
            >Memory</Reference
        >, or <code>nullptr</code> if no <Reference sectionID={SectionID.MEMORY}
            >Memory</Reference
        > is bound.
    </span>
</MethodDescription>

<style lang="scss">
</style>
