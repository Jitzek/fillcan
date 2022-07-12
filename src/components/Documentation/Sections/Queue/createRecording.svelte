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
    code={`CommandRecording* createRecording(unsigned int primaryCommandBufferCount, unsigned int secondaryCommandBufferCount);`}
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
            > should contain.
        </li>
        <li>
            <code>secondaryCommandBufferCount</code><br />
            The amount of Secondary <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > the <Reference sectionID={SectionID.COMMAND_RECORDING}
                >Command Recording</Reference
            > should contain.
        </li>
    </div>
    <span slot="return">
        A pointer to the created <Reference
            sectionID={SectionID.COMMAND_RECORDING}>Command Recording</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
