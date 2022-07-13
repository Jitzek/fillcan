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
    code={`unsigned int createCommandPool(VkCommandPoolCreateFlags flags);`}
/>
<MethodDescription>
    <span slot="details">
        Create a <Reference sectionID={SectionID.COMMAND_POOL}
            >Command Pool</Reference
        >.<br />
        The Queue automatically creates one <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        > on construction, this <Reference sectionID={SectionID.COMMAND_POOL}
            >Command Pool</Reference
        > has both the <code>VK_COMMAND_POOL_CREATE_TRANSIENT_BIT</code>-flag
        and <code>VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT</code>-flag
        set.
    </span>
    <div slot="params">
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandPoolCreateFlagBits.html"
                target="_blank">VkCommandPoolCreateFlagBits</Anchor
            > that specifies usage behavior for the pool and the <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            >
            assigned to it.<br />
            In order to be able to call <Reference
                sectionID={SectionID.COMMAND_BUFFER_reset}>reset</Reference
            > on the <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffers</Reference
            > allocated from this Command Pool the flag
            <code>VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT</code>
            should be set.
        </li>
    </div>
    <span slot="return">
        The index of the newly created <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        >. This index can be used to request the <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        > with <Reference sectionID={SectionID.QUEUE_getCommandPool}
            >getCommandPool</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
