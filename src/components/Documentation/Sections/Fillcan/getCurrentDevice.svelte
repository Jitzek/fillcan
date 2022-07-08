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
    code={`LogicalDevice* getCurrentDevice();`}
/>
<MethodDescription>
    <span slot="details">
        Get the currently selected <Anchor
            href="{getState().URL.documentation}#{SectionID.LOGICAL_DEVICE}"
            >Logical Device</Anchor
        > (selected with <Anchor
            href="{getState().URL
                .documentation}#{SectionID.FILLCAN_selectDevice}"
            >selectDevice</Anchor
        >)</span
    >
    <span slot="returns"
        >A pointer to the currently selected <Anchor
            href="{getState().URL.documentation}#{SectionID.LOGICAL_DEVICE}"
            >Logical Device</Anchor
        >.</span
    >
</MethodDescription>
