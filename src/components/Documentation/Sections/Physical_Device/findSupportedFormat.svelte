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
    code={`const VkFormat findSupportedFormat(std::vector<VkFormat> formats, VkImageTiling tiling, VkFormatFeatureFlags features) const;`}
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
        The first format in the list of given formats that supports the given
        tiling and features.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if none of the given formats supports the
        given tiling and features.
    </span>
</MethodDescription>

<style lang="scss">
</style>
