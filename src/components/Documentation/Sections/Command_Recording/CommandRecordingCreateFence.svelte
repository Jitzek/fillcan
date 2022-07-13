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
    code={`void createFence(LogicalDevice* pLogicalDevice, VkFenceCreateFlags flags = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Create a <Reference sectionID={SectionID.FENCE}>Fence</Reference> which will
        be signaled once this recording has been submitted to the <Reference
            sectionID={SectionID.QUEUE}>Queue</Reference
        > and all work has finished execution.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            The <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > that should own the <Reference sectionID={SectionID.FENCE}
                >Fence</Reference
            >.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFenceCreateFlagBits.html"
                target="_blank">VkFenceCreateFlagBits</Anchor
            > specifying the initial state and behavior of the <Reference
                sectionID={SectionID.FENCE}>Fence</Reference
            >.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
