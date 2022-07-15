<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`VkBufferCreateFlags getFlags();`} />
<MethodDescription>
    <span slot="details">
        Get the flags given in the <Reference
            sectionID={SectionID.BUFFER_Constructor}>Constructor</Reference
        >.
    </span>
    <span slot="return">
        The flags given in the <Reference
            sectionID={SectionID.BUFFER_Constructor}>Constructor</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
