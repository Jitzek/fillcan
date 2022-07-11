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
    code={`std::vector<PhysicalDevice> getSupportedPhysicalDevices();`}
/>
<MethodDescription>
    <span slot="details">
        Get the <Anchor
            href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
            >Physical Devices</Anchor
        > that support the requirements given in the <Anchor
            href="{getState().URL
                .documentation}#{SectionID.DEVICE_POOL_Constructor}"
            >Constructor</Anchor
        >.</span
    >
    <span slot="return"
        >A list of all the <Anchor
            href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
            >Physical Devices</Anchor
        > that meet the requirements for the purposes of this implementation.</span
    >
</MethodDescription>
