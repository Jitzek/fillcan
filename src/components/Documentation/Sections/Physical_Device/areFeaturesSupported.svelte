<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool areFeaturesSupported();`} />
<MethodDescription>
    <span slot="details">
        Whether the device features given in the <Reference
            sectionID={SectionID.PHYSICAL_DEVICE_Constructor}
            >Constructor</Reference
        > are supported.
    </span>
    <span slot="return"
        ><code>true</code> if the device features are supported.
        <code>false</code> if the device features aren't supported.</span
    >
</MethodDescription>

<style lang="scss">
</style>
