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
    code={`ImageView* getImageView(unsigned int index);`}
/>
<MethodDescription>
    <span slot="details"
        >Get a pointer to an <Reference sectionID={SectionID.IMAGE_VIEW}
            >Image View</Reference
        > by index.</span
    >
    <div slot="params">
        <li>
            <code>index</code><br />
            The index the <Reference sectionID={SectionID.IMAGE_VIEW}
                >Image View</Reference
            > to get.
        </li>
    </div>
    <span slot="return"
        >A pointer to the requested <Reference sectionID={SectionID.IMAGE_VIEW}
            >Image View</Reference
        >.</span
    >
</MethodDescription>

<style lang="scss">
</style>
