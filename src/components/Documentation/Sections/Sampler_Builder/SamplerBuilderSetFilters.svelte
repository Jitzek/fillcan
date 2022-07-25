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
    code={`void setFilters(VkFilter magFilter, VkFilter minFilter);`}
/>
<MethodDescription>
    <span slot="details">
        Set the filter modes to use when the <Reference
            sectionID={SectionID.IMAGE}>image</Reference
        > is magnified or minified.
    </span>
    <div slot="params">
        <li>
            <code>magFilter</code><br />
            The filter mode to use when the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > is magnified. This is a member of the <VkReference
                reference="VkFilter"
                version={1.3}>VkFilter</VkReference
            >-enumerant.
        </li>
        <li>
            <code>minFilter</code><br />
            The filter mode to use when the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > is minified. This is a member of the <VkReference
                reference="VkFilter"
                version={1.3}>VkFilter</VkReference
            >-enumerant.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
