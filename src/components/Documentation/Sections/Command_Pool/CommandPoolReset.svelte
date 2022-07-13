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
    code={`bool reset(VkCommandPoolResetFlags flags);`}
/>
<MethodDescription>
    <span slot="details">
        Reset the Command Pool.<br />
        Resets all the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        > allocated from this Command Pool.
    </span>
    <div slot="params">
        <li>
            <code>flags</code><br />
            Additional actions to perform while resetting the command pool. This
            is a bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandPoolResetFlagBits.html"
                target="_blank">VkCommandPoolResetFlagBits</Anchor
            >.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the Command Pool was succesfully reset.
        <code>false</code> if the Command Pool failed to reset.
    </span>
</MethodDescription>

<style lang="scss">
</style>
