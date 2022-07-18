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
    code={`void setFlags(VkImageCreateFlags flags);`}
/>
<MethodDescription>
    <span slot="details">
        Set the flags for the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageCreateFlagBits.html"
                target="_blank">VkImageCreateFlagBits</Anchor
            > that describe some properties of the image.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
