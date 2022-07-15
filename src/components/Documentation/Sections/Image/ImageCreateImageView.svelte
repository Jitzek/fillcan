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
    code={`unsigned int createImageView(
    VkImageViewType viewType, 
    VkFormat format,
    VkImageSubresourceRange subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1},
    VkComponentMapping components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                                    VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY}\n);`}
/>
<MethodDescription>
    <span slot="details"
        >Create an <Reference sectionID={SectionID.IMAGE_VIEW}
            >Image View</Reference
        >.</span
    >
    <div slot="params">
        <li>
            <code>viewType</code><br />
            The type of view to create. The display type must be compatible with
            the parent Image type and is a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewType.html"
                target="_blank">VkImageViewType</Anchor
            >-enumeration, which is larger than the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewType.html"
                target="_blank">VkImageViewType</Anchor
            >-enumeration used when creating the parent Image.
        </li>
        <li>
            <code>format</code><br />
            The format of the new <Reference sectionID={SectionID.IMAGE_VIEW}
                >Image View</Reference
            >. This must be a format compatible with the parent image. If two
            formats have the same number of bits per pixel, they are generally
            considered compatible.
        </li>
        <li>
            <code>subresourceRange</code><br />
            The <Reference sectionID={SectionID.IMAGE_VIEW}
                >Image View</Reference
            > can be a subset of the parent Image. This subset is specified using
            the embedded <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageSubresourceRange.html"
                target="_blank">VkImageSubresourceRange</Anchor
            >-structure.
        </li>
        <li>
            <code>components</code><br />
            The order of the components in the <Reference
                sectionID={SectionID.IMAGE_VIEW}>Image View</Reference
            > may differ from that in the parent Image. This makes it possible, for
            example, to create an RGBA representation of an Image in BGRA format.
            This remapping is specified using an instance of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkComponentMapping.html"
                target="_blank">VkComponentMapping</Anchor
            >-structure.
        </li>
    </div>
    <span slot="return">
        The index of the newly created <Reference
            sectionID={SectionID.IMAGE_VIEW}>Image View</Reference
        >. This index can be used to get the created <Reference
            sectionID={SectionID.IMAGE_VIEW}>Image View</Reference
        > using <Reference sectionID={SectionID.IMAGE_getImageView}
            >getImageView</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
