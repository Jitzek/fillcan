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
    code={`void setImageTiling(VkImageTiling tiling);`}
/>
<MethodDescription>
    <span slot="details">
        Set the sample count for the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>tiling</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageTiling.html"
                target="_blank">VkImageTiling</Anchor
            >-enumerant, which contains only <code>VK_IMAGE_TILING_LINEAR</code>
            or
            <code>VK_IMAGE_TILING_OPTIMAL</code>. Linear tiling means that <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            >
            data is laid out from left to right, top to bottom, so that if the underlying
            memory is mapped and it is written with the CPU, it would form a linear
            <Reference sectionID={SectionID.IMAGE}>image</Reference>. Meanwhile,
            optimal tiling is an opaque display used by Vulkan to store data in
            memory to improve the efficiency of the memory subsystem on the
            device. This is generally what should be chosen unless the <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > needs to be CPU mapped and manipulated. Optimal tiling is likely to
            outperform linear tiling in most operations, and linear tiling may not
            be supported at all for some operations or formats, depending on the
            Vulkan implementation.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
