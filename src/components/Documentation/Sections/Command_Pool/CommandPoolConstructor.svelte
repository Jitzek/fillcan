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
    code={`CommandPool(LogicalDevice* pLogicalDevice, VkCommandPoolCreateFlags flags, unsigned int queueFamilyIndex);`}
/>
<MethodDescription>
    <span slot="details">Create a new Command Pool.</span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > that owns the Command Pool.
        </li>
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
        <li>
            <code>queueFamilyIndex</code><br />
            The family index of <Reference sectionID={SectionID.QUEUE}
                >Queues</Reference
            > where <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffers</Reference
            > allocated from this pool are sent.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkCommandPool.html"
            target="_blank">Vulkan Command Pool</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
