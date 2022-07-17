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
    code={`void setUsage(VkBufferUsageFlags usage);`}
/>
<MethodDescription>
    <span slot="details">
        Set the usage for the <Reference sectionID={SectionID.BUFFER}
            >Buffer</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>usage</code><br />
            A bitmask of members of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferUsageFlagBits.html"
                target="_blank">VkBufferUsageFlagBits</Anchor
            >-enumerant telling Vulkan how the <Reference
                sectionID={SectionID.BUFFER}>Buffer</Reference
            > will be used.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
