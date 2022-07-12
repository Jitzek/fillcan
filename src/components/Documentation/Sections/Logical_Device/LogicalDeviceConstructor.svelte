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
    code={`LogicalDevice(PhysicalDevice* pPhysicalDevice);`}
/>
<MethodDescription>
    <span slot="details"> Create a new Logical Device. </span>
    <div slot="params">
        <li>
            <code>pPhysicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.PHYSICAL_DEVICE}
                >Physical Device</Reference
            > to create a Logical Device from.
        </li>
    </div>
</MethodDescription><br />
The Logical Device can be retrieved using the <Reference
    sectionID={SectionID.FILLCAN}>Fillcan</Reference
> or <Reference sectionID={SectionID.FILLCAN_GRAPHICS}
    >Fillcan Graphics</Reference
> API by calling
<Reference sectionID={SectionID.FILLCAN_selectDevice}>selectDevice</Reference> instead
of manually calling this Constructor.

<style lang="scss">
</style>
