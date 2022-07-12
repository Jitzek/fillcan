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
    code={`const std::optional<VkFormat> findSupportedFormat(
        std::vector<VkFormat> formats, 
        VkImageTiling tiling, 
        VkFormatFeatureFlags features\n) const;`}
/>
<MethodDescription>
    <span slot="details">
        Find a format from a list of given formats which supports the given
        tiling and features.
    </span>
    <div slot="params">
        <li>
            <code>formats</code><br />
            The formats to query support for.
        </li>
        <li>
            <code>tiling</code><br />
            The tiling arrangement of data in an <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > which the format should support. This should be a member of the <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkImageTiling.html"
                target="_blank">VkImageTiling</Anchor
            > enumeration.
        </li>
        <li>
            <code>features</code><br />
            A bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFormatFeatureFlagBits.html"
                target="_blank">VkFormatFeatureFlagBits</Anchor
            > specifying the features supported by a <Reference
                sectionID={SectionID.BUFFER}>Buffer</Reference
            > this format should support.
        </li>
    </div>
    <span slot="return">
        An optional value of the first format in the list of given formats that
        supports the given tiling and features or <Anchor
            href="https://en.cppreference.com/w/cpp/utility/optional/nullopt"
            target="_blank">std::nullopt</Anchor
        > if none of the given formats supports the given tiling and features.
    </span>
</MethodDescription><br />
Example:
<Highlight
    language={cppHighlight}
    code={`std::vector<VkFormat> formats = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
VkFormatFeatureFlags features = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;

std::optional<VkFormat> optFormat = fillcan.getCurrentDevice()->getPhysicalDevice()->findSupportedFormat(
    formats, tiling, features
);

if (!optFormat.has_value()) {
    throw std::runtime_error("Failed to find a supported format");
}

VkFormat supportedFormat = optFormat.value();`}
/>

<style lang="scss">
</style>
