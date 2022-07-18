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
    code={`const std::vector<unsigned int>& getComputeQueueFamilyIndices() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get the queue family indices for the compute <Reference
            sectionID={SectionID.QUEUE}>Queues</Reference
        >.
    </span>
    <span slot="return">
        The queue family indices for the compute Queues.
    </span>
</MethodDescription>

<style lang="scss">
</style>
