<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
    import Image from "../Image/Image.svelte";
</script>

<Highlight
    language={cppHighlight}
    code={`void setInitialLayout(VkImageLayout initialLayout);`}
/>
<MethodDescription>
    <span slot="details">
        Set the queue family indices for the <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>initialLayout</code><br />
            <Reference sectionID={SectionID.IMAGE}>Images</Reference> have a layout,
            which partially indicates how they will be used at a given time. This
            field determines the layout in which the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > is created. The available layouts are the members of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html"
                target="_blank">VkImageLayout</Anchor
            >-enumerant.<br />
            <Reference sectionID={SectionID.IMAGE}>Images</Reference> should initially
            be created in the format
            <code>VK_IMAGE_LAYOUT_UNDEFINED</code>
            or <code>VK_IMAGE_LAYOUT_PREINITIALIZED</code>.
            <code>VK_IMAGE_LAYOUT_PREINITIALIZED</code>
            should only be used if there is data in memory that is bound immediately
            to the <Reference sectionID={SectionID.IMAGE}>image</Reference> source.
            <code>VK_IMAGE_LAYOUT_UNDEFINED</code>
            should be used when moving the resource to another layout before use.
            <Reference sectionID={SectionID.IMAGE}>Images</Reference> can be moved
            out of the
            <code>VK_IMAGE_LAYOUT_UNDEFINED</code> layout at any time with little
            or no time cost.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
