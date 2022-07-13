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
    code={`void freeCommandBuffers(std::vector<CommandBuffer*> pCommandBuffers);`}
/>
<MethodDescription>
    <span slot="details">
        Free the given Command Buffers.<br />
        Freeing a <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffer</Reference
        > does not necessarily free all its resources, but returns them to the Command
        Pool from which they were allocated.
    </span>
    <div slot="params">
        <li>
            <code>pCommandBuffers</code><br />
            The <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffers</Reference
            > to free.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
