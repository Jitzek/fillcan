<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void unmap();`} />
<MethodDescription>
    <span slot="details">Return a pointer to the mapped memory area.</span>
    <span slot="return">
        The mapped memory mapped with <Reference
            sectionID={SectionID.MEMORY_map}>map</Reference
        > or <code>nullptr</code> if no memory is mapped.
    </span>
</MethodDescription>

<style lang="scss">
</style>
