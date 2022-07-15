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
    code={`void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, std::vector<VkBufferCopy>& regions);`}
/>
<MethodDescription>
    <span slot="details">Copy this Buffer's data to a given Buffer.</span>
    <div slot="params">
        <li>
            <code>pCommandBuffer</code><br />
            The <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffer</Reference
            > to use to execute the copy.
        </li>
        <li>
            <code>pBuffer</code><br />
            A pointer to the Buffer to copy this Buffer's data to.
        </li>
        <li>
            <code>regions</code><br />
            An array of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCopy.html"
                target="_blank">VkBufferCopy</Anchor
            >-structures, each of which describes a region of data to copy.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout dstLayout, std::vector<VkBufferImageCopy>& regions);`}
/>
<MethodDescription>
    <span slot="details"
        >Copy this Buffer's data to a given <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        >.</span
    >
    <div slot="params">
        <li>
            <code>pCommandBuffer</code><br />
            The <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffer</Reference
            > to use to execute the copy.
        </li>
        <li>
            <code>pImage</code><br />
            A pointer to the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > to copy this Buffer's data to.
        </li>
        <li>
            <code>dstLayout</code><br />
            The layout of the destination <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > subresources for the copy. This should be a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html"
                target="_blank">VkImageLayout</Anchor
            >-enumerant.<br />
            This is most likely either
            <code>VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL</code>,
            <code>VK_IMAGE_LAYOUT_GENERAL</code>
            or <code>VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR</code>.
        </li>
        <li>
            <code>pBuffer</code><br />
            A pointer to the Buffer to copy this Buffer's data to.
        </li>
        <li>
            <code>regions</code><br />
            An array of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCopy.html"
                target="_blank">VkBufferCopy</Anchor
            >-structures, each of which describes a region of data to copy.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
