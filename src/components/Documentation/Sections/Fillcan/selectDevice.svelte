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
    code={`LogicalDevice* selectDevice(unsigned int deviceIndex = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Select a <Anchor
            href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
            >physical device</Anchor
        > by index to create a <Anchor
            href="{getState().URL.documentation}#{SectionID.LOGICAL_DEVICE}"
            >logical device</Anchor
        > of.
    </span>
    <span slot="returns"
        >A pointer to the created <Anchor
            href="{getState().URL.documentation}#{SectionID.LOGICAL_DEVICE}"
            >logical device</Anchor
        >.
    </span>
</MethodDescription><br />
If a device is selected, a pointer to the logical device can also be retrieved using
<Anchor
    href="{getState().URL.documentation}#{SectionID.FILLCAN_getCurrentDevice}"
    >getCurrentDevice</Anchor
>.
