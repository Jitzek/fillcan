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
    code={`CommandRecording* createRecording(
        unsigned int primaryCommandBufferCount, 
        unsigned int secondaryCommandBufferCount,
        CommandPool* pCommandPool = nullptr\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a <Reference sectionID={SectionID.COMMAND_RECORDING}
            >Command Recording</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>primaryCommandBufferCount</code><br />
            The amount of Primary <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > the <Reference sectionID={SectionID.COMMAND_RECORDING}
                >Command Recording</Reference
            > should allocate.
        </li>
        <li>
            <code>secondaryCommandBufferCount</code><br />
            The amount of Secondary <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > the <Reference sectionID={SectionID.COMMAND_RECORDING}
                >Command Recording</Reference
            > should allocate.
        </li>
        <li>
            <code>pCommandPool</code><br />
            The <Reference sectionID={SectionID.COMMAND_POOL}
                >Command Pool</Reference
            > to allocate the <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffers</Reference
            > from.<br />
            If <code>nullptr</code>, it will default to the first <Reference
                sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
            > it can find.
        </li>
    </div>
    <span slot="return">
        A pointer to the created <Reference
            sectionID={SectionID.COMMAND_RECORDING}>Command Recording</Reference
        >.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if no <Reference
            sectionID={SectionID.COMMAND_POOL}>Command Pools</Reference
        > are allocated.
    </span>
</MethodDescription>

<style lang="scss">
</style>
