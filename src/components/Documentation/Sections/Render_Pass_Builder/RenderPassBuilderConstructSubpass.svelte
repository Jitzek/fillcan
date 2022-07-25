<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`unsigned int constructSubpass();`} />
<MethodDescription>
    <span slot="details">
        Construct a new subpass from the current batch of attachments. The
        current batch contains all the attachments added after the last subpass
        construction or after the initialization of the builder.
    </span>
    <span slot="return"> The index of the newly constructed subpass. </span>
</MethodDescription>

<style lang="scss">
</style>
