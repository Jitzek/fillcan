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
    code={`static bool s_resetAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences);`}
/>
<MethodDescription>
    <span slot="details">Reset all given Fences.</span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            The <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > which owns the given Fences.
        </li>
        <li>
            <code>pFences</code><br />
            A list of pointers to the <Reference sectionID={SectionID.FENCE}
                >Fences</Reference
            > to reset.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if all the Fences were succesfully reset.
        <code>false</code> if not all Fences could be reset.
    </span>
</MethodDescription>

<style lang="scss">
</style>
