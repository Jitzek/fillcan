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
    code={`const std::vector<uint32_t>& getQueueFamilyIndices() const;`}
/>
<MethodDescription>
    <span slot="details">
        The <Reference sectionID={SectionID.QUEUE}>Queue</Reference> families between
        which an <Reference sectionID={SectionID.IMAGE}>Image</Reference> is shared.<br
        />
        For Fillcan version {getState().Fillcan.version} this list will always be
        empty, as shared <Reference sectionID={SectionID.QUEUE}
            >Queues</Reference
        > are not yet supported for Swapchain <Reference
            sectionID={SectionID.IMAGE}>Images</Reference
        >.
    </span>
    <span slot="return">
        A list of <Reference sectionID={SectionID.QUEUE}>Queue</Reference> family
        indices between which an <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        > is shared.
    </span>
</MethodDescription>

<style lang="scss">
</style>
