<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`CommandRecording* Fillcan::beginSingleTimeRecording(Queue* pQueue);`}
/>
<MethodDescription>
    <span slot="details">
        Start a <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_RECORDING}"
            >Command Recording</Anchor
        > with a given <Anchor
            href="{getState().URL.documentation}#{SectionID.QUEUE}"
            >Queue</Anchor
        >.<br />
        Creates a <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_RECORDING}"
            >Command Recording</Anchor
        > using the given Queue pointer. This <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_RECORDING}"
            >Command Recording</Anchor
        > will contain 1 (one) Primary <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_BUFFER}"
            >Command Buffer</Anchor
        > and 0 (zero) Secondary <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_BUFFER}"
            >Command Buffers</Anchor
        >. To end the recording, call <Anchor
            href="{getState().URL
                .documentation}#{SectionID.LOGICAL_DEVICE_endSingleTimeCommandRecording}"
            >endSingleTimeRecording</Anchor
        >.
    </span>
    <div slot="params">
        <li>
            <code>pQueue</code><br />
            A pointer to the <Anchor
                href="{getState().URL.documentation}#{SectionID.QUEUE}"
                >Queue</Anchor
            > from which a <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.COMMAND_RECORDING}"
                >Command Recording</Anchor
            > will be created from.
        </li>
    </div>
    <span slot="return"
        >A pointer to the created <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_RECORDING}"
            >Command Recording</Anchor
        >.</span
    >
</MethodDescription>
