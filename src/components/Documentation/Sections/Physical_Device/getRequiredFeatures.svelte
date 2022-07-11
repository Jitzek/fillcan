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
    code={`const VkPhysicalDeviceFeatures& getRequiredFeatures() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get the device features (given in the <Reference
            sectionID={SectionID.PHYSICAL_DEVICE_Constructor}
            >Constructor</Reference
        >) this Physical Device should support.
    </span>
    <span slot="return">A list of the required device features.</span>
</MethodDescription>

<style lang="scss">
</style>
