<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`int getPresentQueueFamilyIndex();`} />
<MethodDescription>
    <span slot="details">
        Get the queue family index for the present <Reference
            sectionID={SectionID.QUEUE}>Queue</Reference
        >.
    </span>
    <span slot="return">
        the queue family index for the present Queue or <code>-1</code> if no
        present
        <Reference sectionID={SectionID.QUEUE}>Queue</Reference> was found.</span
    >
</MethodDescription>

<style lang="scss">
</style>
