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
    code={`void setLogicalDevice(LogicalDevice* pLogicalDevice);`}
/>
<MethodDescription>
    <span slot="details">
        Set the <Reference sectionID={SectionID.LOGICAL_DEVICE}
            >Logical Device</Reference
        > for the <Reference sectionID={SectionID.BUFFER}>Buffer</Reference>.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the <Reference sectionID={SectionID.BUFFER}>Buffer</Reference> should
            be associated with.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
