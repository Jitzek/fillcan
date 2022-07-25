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
    code={`void setAddressModes(VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW);`}
/>
<MethodDescription>
    <span slot="details">
        Set the address modes which are used to select the transformer applied
        to texture coordinates that would otherwise be sampled outside the
        <Reference sectionID={SectionID.IMAGE}>image</Reference>. These are
        members of the <VkReference
            reference="VkSamplerAddressMode"
            version={1.3}>VkSamplerAddressMode</VkReference
        >-enumerant.
    </span>
    <div slot="params">
        <li>
            <code>addressModeU</code><br />
            U is the X within the convention of texture space coordinates.
        </li>
        <li>
            <code>addressModeV</code><br />
            V is the Y within the convention of texture space coordinates.
        </li>
        <li>
            <code>addressModeW</code><br />
            W is the Z within the convention of texture space coordinates.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
