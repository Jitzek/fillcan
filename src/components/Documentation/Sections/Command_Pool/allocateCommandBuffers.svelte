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
    code={`std::vector<CommandBuffer*> allocateCommandBuffers(VkCommandBufferLevel level, unsigned int commandBufferCount);`}
/>
<MethodDescription>
    <span slot="details">Allocate Command Buffers from the pool.</span>
    <div slot="params">
        <li>
            <code>level</code><br />
            The level at which the allocated Command Buffers operate. This should
            be a member of the <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferLevel.html"
                >VkCommandBufferLevel</Anchor
            >-enumerant.
        </li>
        <li>
            <code>commandBufferCount</code><br />
            The amount of <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffers</Reference
            > to allocate.
        </li>
    </div>
    <span slot="return">
        A list of pointers to the allocated <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
