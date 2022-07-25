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
    code={`void setMipmapMode(VkSamplerMipmapMode mipmapMode);`}
/>
<MethodDescription>
    <span slot="details">
        Set how mipmaps are used in the <Reference sectionID={SectionID.IMAGE}
            >image</Reference
        > when it is sampled.
    </span>
    <div slot="params">
        <li>
            <code>mipmapMode</code><br />
            How mipmaps are used in the <Reference sectionID={SectionID.IMAGE}
                >image</Reference
            > when it is sampled. This is a member of the <VkReference
                reference="VkSamplerMipmapMode"
                version={1.3}>VkSamplerMipmapMode</VkReference
            >-enumerant. If the mipmap mode is
            <code>VK_SAMPLER_MIPMAP_MODE_NEAREST</code>, the selected mipmap
            level is rounded down to the next lowest integer, and then that
            level is sampled as if it were a single-level image. When the mipmap
            mode is <code>VK_SAMPLER_MIPMAP_MODE_LINEAR</code>, a sample is
            taken from each of the next-lower and next-higher levels using the
            filter mode selected by the <code>minFilter</code> field, and then
            those two samples are further combined using a weighted average,
            similar to how the samples are combined during linear sampling, as
            previously described.<br />
            Note that this filter mode only applies to minification, which is the
            process of sampling from a different mipmap level than the base level.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
