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
    code={`void endSingleTimeRecording(CommandRecording* pCommandRecording);`}
/>
<MethodDescription>
    <span slot="details">
        End a Command Recording.<br />
        Ends a <Anchor
            href="{getState().URL.documentation}#{SectionID.COMMAND_RECORDING}"
            >Command Recording</Anchor
        > (preferably created using <Anchor
            href="{getState().URL
                .documentation}#{SectionID.LOGICAL_DEVICE_beginSingleTimeCommandRecording}"
            >beginSingleTimeRecording</Anchor
        >), submits the recording and waits for the <Anchor
            href="{getState().URL.documentation}#{SectionID.QUEUE}"
            >Queue</Anchor
        > to idle before returning.
    </span>
    <div slot="params">
        <li>
            <code>pCommandRecording</code><br />
            A pointer to the <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.COMMAND_RECORDING}"
                >Command Recording</Anchor
            > to end.
        </li>
    </div>
</MethodDescription>
