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
    code={`std::unique_ptr<ComputePipeline> getResult();`}
/>
<MethodDescription>
    <span slot="details">
        Get the resulting <Reference sectionID={SectionID.COMPUTE_PIPELINE}
            >Compute Pipeline</Reference
        >.
    </span>
    <span slot="return">
        A <Anchor
            href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
            target="_blank">unique pointer</Anchor
        > to the <Reference sectionID={SectionID.COMPUTE_PIPELINE}
            >Compute Pipeline</Reference
        >, it's ownership will be moved.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.COMPUTE_PIPELINE}>Compute Pipeline</Reference
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
