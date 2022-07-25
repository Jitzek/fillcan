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
    code={`void setBorderColor(VkBorderColor borderColor);`}
/>
<MethodDescription>
    <span slot="details"> Set the border color. </span>
    <div slot="params">
        <li>
            <code>borderColor</code><br />
            The border color used in place of data from the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > if
            <code>addressmodeU</code>,
            <code>addressmodeV</code> and/or <code>addressmodeW</code> is set to
            <code>VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER</code> using <Reference
                sectionID={SectionID.SAMPLER_BUILDER_setAddressModes}
                >setAddressModes</Reference
            >. This is a member of the <VkReference
                reference="VkBorderColor"
                version={1.3}>VkBorderColor</VkReference
            >-enumerant.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
