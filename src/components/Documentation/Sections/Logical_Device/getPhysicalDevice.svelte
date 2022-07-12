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
    code={`const PhysicalDevice* getPhysicalDevice() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get a pointer to the <Reference sectionID={SectionID.PHYSICAL_DEVICE}
            >Physical Device</Reference
        > this Logical Device is constructed around.
    </span>
    <span slot="return">
        A pointer to the <Reference sectionID={SectionID.PHYSICAL_DEVICE}
            >Physical Device</Reference
        > this Logical Device is constructed around.
    </span>
</MethodDescription>

<style lang="scss">
</style>
