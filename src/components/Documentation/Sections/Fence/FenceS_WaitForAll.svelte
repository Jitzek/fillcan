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
    code={`static bool s_waitForAll(LogicalDevice* pLogicalDevice, std::vector<Fence*> pFences, uint64_t timeout = UINT64_MAX);`}
/>
<MethodDescription>
    <span slot="details">Wait for all given Fences to be signaled.</span>
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
            > to wait for.
        </li>
        <li>
            <code>timeout</code><br />
            The timeout period in units of nanoseconds to wait before returning.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if all the Fences were succesfully waited for.
        <code>false</code> if the timeout expired.
    </span>
</MethodDescription>

<style lang="scss">
</style>
