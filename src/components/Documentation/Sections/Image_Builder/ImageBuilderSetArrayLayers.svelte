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
    code={`void setArrayLayers(unsigned int arrayLayers);`}
/>
<MethodDescription>
    <span slot="details">
        Set the number of array layers for the <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>arrayLayers</code><br />
            The amount of <Reference sectionID={SectionID.IMAGE}
                >Images</Reference
            > each mipmap level of the <Reference sectionID={SectionID.IMAGE}
                >Images</Reference
            > has.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
