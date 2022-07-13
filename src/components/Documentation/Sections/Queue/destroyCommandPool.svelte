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
    code={`void destroyCommandPool(unsigned int index);`}
/>
<MethodDescription>
    <span slot="details"
        >Destroy a <Reference sectionID={SectionID.COMMAND_POOL}
            >Command Pool</Reference
        > by index.</span
    >
    <div slot="params">
        <li>
            <code>index</code><br />
            The index of the <Reference sectionID={SectionID.COMMAND_POOL}
                >Command Pool</Reference
            > to destroy. This index was returned by <Reference
                sectionID={SectionID.QUEUE_createCommandPool}
                >createCommandPool</Reference
            >.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
