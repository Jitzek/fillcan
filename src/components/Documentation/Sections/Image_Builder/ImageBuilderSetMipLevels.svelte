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
    code={`void setMipLevels(unsigned int mipLevels);`}
/>
<MethodDescription>
    <span slot="details">
        Set the number of mipmap levels for the <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>mipLevels</code><br />
            The number of mipmap levels to create in the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            >.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
