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
    code={`void setImageType(VkImageType type);`}
/>
<MethodDescription>
    <span slot="details">
        Set the image type for
        the <Reference sectionID={SectionID.IMAGE}>Image</Reference>.
    </span>
    <div slot="params">
        <li>
            <code>type</code><br />
            The type of <Reference sectionID={SectionID.IMAGE}>Image</Reference>
            being created. The <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > type is essentially the dimensionality of the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > and can be <code>VK_IMAGE_TYPE_1D</code>,
            <code>VK_IMAGE_TYPE_2D</code>
            or <code>VK_IMAGE_TYPE_3D</code>
            for a 1D, 2D or 3D <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > respectively.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
