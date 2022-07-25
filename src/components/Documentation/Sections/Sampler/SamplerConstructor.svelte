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
    code={`Sampler(
    LogicalDevice* pLogicalDevice, 
    VkFilter magFilter, 
    VkFilter minFilter, 
    VkSamplerMipmapMode mipmapMode,
    VkSamplerAddressMode addressModeU, 
    VkSamplerAddressMode addressModeV, 
    VkSamplerAddressMode addressModeW, 
    float mipLodBias,
    VkBool32 anisotropyEnable, 
    float maxAnisotropy, 
    VkBool32 compareEnable, 
    VkCompareOp compareOp, 
    float minLod, 
    float maxLod,
    VkBorderColor borderColor, 
    VkBool32 unnormalizedCoordinates
);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Sampler.<br />
        It is recommended to not create a Sampler by it's Constructor, but to use
        a
        <Reference sectionID={SectionID.SAMPLER_BUILDER}
            >Sampler Builder</Reference
        > instead.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Sampler should be associated with.
        </li>
        <li>
            <code>magFilter</code><br />
            The filter mode to use when the image is magnified. This is a member
            of the <VkReference reference="VkFilter" version={1.3}
                >VkFilter</VkReference
            >-enumerant.
        </li>
        <li>
            <code>minFilter</code><br />
            The filter mode to use when the image is minified. This is a member of
            the <VkReference reference="VkFilter" version={1.3}
                >VkFilter</VkReference
            >-enumerant.
        </li>
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
        <li>
            <code>addressModeU</code><br />
            Used to select the transformer applied to texture coordinates that would
            otherwise be sampled outside the image. This is a member of the <VkReference
                reference="VkSamplerAddressMode"
                version={1.3}>VkSamplerAddressMode</VkReference
            >-enumerant.<br />
            U is the X within the convention of texture space coordinates.
        </li>
        <li>
            <code>addressModeV</code><br />
            Used to select the transformer applied to texture coordinates that would
            otherwise be sampled outside the image. This is a member of the <VkReference
                reference="VkSamplerAddressMode"
                version={1.3}>VkSamplerAddressMode</VkReference
            >-enumerant.<br />
            V is the Y within the convention of texture space coordinates.
        </li>
        <li>
            <code>addressModeW</code><br />
            Used to select the transformer applied to texture coordinates that would
            otherwise be sampled outside the image. This is a member of the <VkReference
                reference="VkSamplerAddressMode"
                version={1.3}>VkSamplerAddressMode</VkReference
            >-enumerant.<br />
            W is the Z within the convention of texture space coordinates.
        </li>
        <li>
            <code>mipLodBias</code><br />
            A floating-point bias that is added to the computed level of detail before
            making mipmap selection. This can push the level of detail up or down
            in the mipmap chain to make the resulting filtered texture look sharper
            or fainter than it would otherwise.
        </li>
        <li>
            <code>anisotropyEnable</code><br />
            If anisotropic filtering is to be used, it can be set to
            <code>VK_TRUE</code>. If not, it can be set to
            <code>VK_FALSE</code>. Anisotropic filtering generally works by
            considering a projected footprint of the area to be sampled (or
            "sampled") rather than using a fixed 2x2 footprint. An approximation
            of a surface sample is formed by taking many samples within the
            footprint.
        </li>
        <li>
            <code>maxAnisotropy</code><br />
            Because the number of samples taken can be quite large, anisotropic filtering
            can have a negative effect on performance. Also, in extreme cases, the
            projected footprint can be quite large, and this can result in a large
            area and a correspondingly blurry filter result. To mitigate these effects,
            the maximum amount of anisotropy can be locked by setting
            <code>maxAnisotropy</code>
            to a value between <code>1.0f</code> and the maximum value supported
            by the device. The maximum values can be determined by calling <Reference
                sectionID={SectionID.PHYSICAL_DEVICE_getProperties}
                >getProperties</Reference
            >
            and inspecting the <code>maxSamplerAnisotropy</code> member of the
            embedded <VkReference
                reference="VkPhysicalDeviceLimits"
                version={1.3}>VkPhysicalDeviceLimits</VkReference
            >
            structure.
        </li>
        <li>
            <code>compareEnable</code><br />
            of the comparison instead of the raw values stored in the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            >. When this mode is enabled, the comparison is performed on each
            sample taken from the <Reference sectionID={SectionID.IMAGE}
                >image</Reference
            >, and the resulting value is the fraction of the total number of
            samples taken that passed the test. This can be used to implement a
            technique known as percentage closer filtering or PCF. To enable
            this mode, <code>compareEnable</code>
            must be set to <code>VK_TRUE</code>
            and the compare operation must be set to <code>compareOp</code>.
        </li>
        <li>
            <code>compareOp</code><br />
            A member of the <VkReference reference="VkCompareOp" version={1.3}
                >VkCompareOp</VkReference
            >-enumeration, which is used in many places in Vulkan, including the
            <Reference sectionID={SectionID.GRAPHICS_PIPELINE}
                >graphical pipeline</Reference
            >. This is the enumeration used to specify the depth test operation.
        </li>
        <li>
            <code>minLod</code><br />
            The lowest mipmaps (highest resolution) to sample from. The sampler can
            be configured to limit sampling to a subset of the mip levels in an <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            >
            with mipmaps. The range of mipmaps to sample from is specified in
            <code>minLod</code>
            and <code>maxLod</code>.
        </li>
        <li>
            <code>maxLod</code><br />
            The highest mipmaps (lowest resolution) to sample from.
        </li>
        <li>
            <code>borderColor</code><br />
            The border color used in place of data from the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > if
            <code>addressmodeU</code>,
            <code>addressmodeV</code> and/or <code>addressmodeW</code> is set to
            <code>VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER</code>. This is a
            member of the <VkReference reference="VkBorderColor" version={1.3}
                >VkBorderColor</VkReference
            >-enumerant.
        </li>
        <li>
            <code>unnormalizedCoordinates</code><br />
            A flag that, when set to <code>VK_TRUE</code>, indicates that the
            coordinates used to extract from the image are in raw texel units,
            rather than a value normalized between <code>0.0</code> and
            <code>1.0</code>
            for each dimension of the texture. This allows texels to be explicitly
            extracted from the image. However, there are several limitations in this
            mode. When <code>unnormalizedCoordinates</code>
            is set to <code>VK_TRUE</code>,
            <code>minFilter</code> and <code>magFilter</code> must be the same,
            <code>mipmapMode</code>
            must be set to <code>VK_SAMPLER_MIPMAP_MODE_NEAREST</code> and
            <code>anisotropyEnable</code>
            and
            <code>compareEnable</code> must be set to <code>VK_FALSE</code>.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <VkReference
            reference="VkSampler"
            version={1.3}>Vulkan Sampler</VkReference
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
