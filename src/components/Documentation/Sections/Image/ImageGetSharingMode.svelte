<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`VkSharingMode getSharingMode();`} />
<MethodDescription>
    <span slot="details">
        Get the sharing mode given in the <Reference
            sectionID={SectionID.BUFFER_Constructor}>Constructor</Reference
        >.
    </span>
    <span slot="return">
        The sharing mode given in the <Reference
            sectionID={SectionID.BUFFER_Constructor}>Constructor</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
