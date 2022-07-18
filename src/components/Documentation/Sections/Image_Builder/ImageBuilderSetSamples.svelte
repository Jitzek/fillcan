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
    code={`void setSamples(VkSampleCountFlagBits samples);`}
/>
<MethodDescription>
    <span slot="details">
        Set the sample count for the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>samples</code><br />
            The number of samples in the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            >. It must be a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleCountFlagBits.html"
                target="_blank">VkSampleCountFlagBits</Anchor
            >-enumerant.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
