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
    code={`void setFormat(VkFormat format);`}
/>
<MethodDescription>
    <span slot="details">
        Set the format for the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>format</code><br />
            Describes how texel data is stored in memory and interpreted by Vulkan.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
