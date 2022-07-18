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
    code={`void setExtent(VkExtent3D extent);`}
/>
<MethodDescription>
    <span slot="details">
        Set the extent for the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>extent</code><br />
            The size of the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > in texels. This should be an instance of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkExtent3D.html"
                target="_blank">VkExtent3D</Anchor
            >
            structure , which has three members: <code>width</code>,
            <code>height</code>, and <code>depth</code>. These should be set
            respectively to the width, height and depth of the desired <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            >. For 1D <Reference sectionID={SectionID.IMAGE}>Images</Reference>,
            the height should be set to <code>1</code>, and for 1D and 2D
            <Reference sectionID={SectionID.IMAGE}>Images</Reference>, the depth
            should be set to <code>1</code>.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
