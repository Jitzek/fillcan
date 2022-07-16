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
    code={`ImageView(
    LogicalDevice* pLogicalDevice, 
    Image* pImage, 
    VkImageViewType viewType, 
    VkFormat format, 
    VkImageSubresourceRange subresourceRange,
    VkComponentMapping components\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Image View.<br />
        It is recommended to not create an Image View by it's Constructor, but to
        use
        <Reference sectionID={SectionID.IMAGE_createImageView}
            >createImageView</Reference
        > instead.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Image View should be associated with.
        </li>
        <li>
            <code>pBuffer</code><br />
            A pointer to the parent <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > to create a Image View of.
        </li>
        <li>
            <code>viewType</code><br />
            The type of view to create. The display type must be compatible with
            the parent Image type and is a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewType.html"
                target="_blank">VkImageViewType</Anchor
            >-enumeration, which is larger than the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewType.html"
                target="_blank">VkImageViewType</Anchor
            >-enumeration used when creating the parent <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            >.
        </li>
        <li>
            <code>format</code><br />
            The format of the new Image View. This must be a format compatible with
            the parent <Reference sectionID={SectionID.IMAGE}>Image</Reference>.
            If two formats have the same number of bits per pixel, they are
            generally considered compatible.
        </li>
        <li>
            <code>subresourceRange</code><br />
            The Image View can be a subset of the parent <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            >. This subset is specified using the embedded <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageSubresourceRange.html"
                target="_blank">VkImageSubresourceRange</Anchor
            >-structure.
        </li>
        <li>
            <code>components</code><br />
            The order of the components in the Image View may differ from that in
            the parent <Reference sectionID={SectionID.IMAGE}>Image</Reference>.
            This makes it possible, for example, to create an RGBA
            representation of an Image in BGRA format. This remapping is
            specified using an instance of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkComponentMapping.html"
                target="_blank">VkComponentMapping</Anchor
            >-structure.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
