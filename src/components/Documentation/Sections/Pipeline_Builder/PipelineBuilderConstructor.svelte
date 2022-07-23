<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`PipelineBuilder();`} />
<MethodDescription>
    <span slot="details">
        Create a new Pipeline Builder.<br />
        The <code>Pipeline Builder</code> class is meant to be extended as it
        only asks for the generic information shared by all <Reference
            sectionID={SectionID.PIPELINE}>pipelines</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
