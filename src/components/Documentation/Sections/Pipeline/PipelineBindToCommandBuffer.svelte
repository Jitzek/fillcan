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
    code={`void bindToCommandBuffer(CommandBuffer* pCommandBuffer);`}
/>
<MethodDescription>
    <span slot="details">
        Bind the pipeline to a <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        >.<br />
        Before a pipeline can be used, it must be bound to a <Reference
            sectionID={SectionID.COMMAND_BUFFER}>command buffer</Reference
        > that executes draw or send commands. This can be done with a command. When
        this command is executed, the current pipeline (and all shaders in it) is
        used to process the commands.
    </span>
    <div slot="params">
        <li>
            <code>pCommandBuffer</code><br />
            A pointer to the <Reference sectionID={SectionID.COMMAND_BUFFER}
                >command buffer</Reference
            > to bind to.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the pipeline bindpoint is not set, this
        should be done by the class that extends the pipeline.
    </span>
</MethodDescription>

<style lang="scss">
</style>
