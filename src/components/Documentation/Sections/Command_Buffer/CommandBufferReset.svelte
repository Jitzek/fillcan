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
    code={`bool reset(VkCommandBufferResetFlags flags = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Start the Command Buffer, which resets it to an initial state.<br />

        Many applications use a similar set of commands to render all or part of
        each frame. Therefore, it is likely that similar Command Buffers are
        included in the application over and over again.<br />
        Allocating and freeing Command Buffers every frame is a relatively heavy
        operation. If the application reuses a Command Buffer many times in a row
        for similar work, it may be more efficient to reset the Command Buffer.<br
        />
        This effectively restores the Command Buffer to its original state, but does
        not necessarily interact with the <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
        > to do so. Therefore, if the Command Buffer dynamically allocates resources
        from the <Reference sectionID={SectionID.COMMAND_POOL}
            >Command Pool</Reference
        > as the Command Buffer grows, the Command Buffer can hold onto those resources
        and avoid the cost of reallocation the next time it is rebuilt.
    </span>
    <div slot="params">
        <li>
            <code>flags</code><br />
            Additional actions to perform while resetting the command buffer.<br
            />
            This is a bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBufferResetFlagBits.html"
                target="_blank">VkCommandBufferResetFlagBits</Anchor
            >.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the Command Buffer was succesfully reset.
        <code>false</code> if the Command Buffer failed to reset.
    </span>
</MethodDescription>

<style lang="scss">
</style>
