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
    code={`const std::vector<PhysicalDevice> getSupportedPhysicalDevices() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get the supported <Anchor
            href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
            >Physical Devices</Anchor
        >.
    </span>
    <span slot="returns">
        A list of all the <Anchor
            href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
            >Physical Devices</Anchor
        > that meet the requirements for the purposes of this implementation.
    </span>
</MethodDescription>
