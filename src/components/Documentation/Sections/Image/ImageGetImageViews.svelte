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
    code={`std::vector<ImageView*> getImageViews();`}
/>
<MethodDescription>
    <span slot="details"
        >Get all the created <Reference sectionID={SectionID.IMAGE_VIEW}
            >Image Views</Reference
        >.</span
    >
    <span slot="return"
        >A list of pointers to the created <Reference
            sectionID={SectionID.IMAGE_VIEW}>Image Views</Reference
        >.</span
    >
</MethodDescription>

<style lang="scss">
</style>
