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
    code={`void enableUnnormalizedCoordinates();`}
/>
<MethodDescription>
    <span slot="details"
        >Enable unnormalized coordinates.<br />
        When enabled, indicates that the coordinates used to extract from the <Reference
            sectionID={SectionID.IMAGE}>image</Reference
        > are in raw texel units, rather than a value normalized between
        <code>0.0</code>
        and
        <code>1.0</code>
        for each dimension of the texture. This allows texels to be explicitly extracted
        from the <Reference sectionID={SectionID.IMAGE}>image</Reference>.
        However, there are several limitations in this mode. When
        <code>unnormalizedCoordinates</code>
        is enabled,
        <code>minFilter</code> and <code>magFilter</code> (see <Reference
            sectionID={SectionID.SAMPLER_BUILDER_setFilters}
            >setFilters</Reference
        >) must be the same, <code>mipmapMode</code> (see <Reference
            sectionID={SectionID.SAMPLER_BUILDER_setMipmapMode}
            >setMipmapMode</Reference
        >) must be set to <code>VK_SAMPLER_MIPMAP_MODE_NEAREST</code> and
        <code>anisotropyEnable</code>
        (see <Reference sectionID={SectionID.SAMPLER_BUILDER_setMaxAnisotropy}
            >setMaxAnisotropy</Reference
        > and <Reference
            sectionID={SectionID.SAMPLER_BUILDER_unsetMaxAnisotropy}
            >unsetMaxAnisotropy</Reference
        >) and
        <code>compareEnable</code> (see <Reference
            sectionID={SectionID.SAMPLER_BUILDER_setCompareOp}
            >setCompareOp</Reference
        > and <Reference sectionID={SectionID.SAMPLER_BUILDER_unsetCompareOp}
            >unsetCompareOp</Reference
        >) must be set to <code>VK_FALSE</code>.</span
    >
</MethodDescription>

<style lang="scss">
</style>
