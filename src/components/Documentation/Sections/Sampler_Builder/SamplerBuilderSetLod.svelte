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

<Highlight
    language={cppHighlight}
    code={`void setLod(float minLod, float maxLod);`}
/>
<MethodDescription>
    <span slot="details">
        The <Reference sectionID={SectionID.SAMPLER}>sampler</Reference> can be configured
        to limit sampling to a subset of the mip levels in an <Reference
            sectionID={SectionID.IMAGE}>image</Reference
        > with mipmaps. The range of mipmaps to sample from is specified in
        <code>minLod</code>
        and <code>maxLod</code>.
    </span>
    <div slot="params">
        <li>
            <code>minLod</code><br />
            The lowest mipmaps (highest resolution) to sample from.
        </li>
        <li>
            <code>maxLod</code><br />
            The highest mipmaps (lowest resolution) to sample from.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
