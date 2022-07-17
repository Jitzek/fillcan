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
    code={`void setQueueFamilyIndices(std::vector<uint32_t>& queueFamilyIndices);`}
/>
<MethodDescription>
    <span slot="details">
        Set the queue family indices for the <Reference
            sectionID={SectionID.BUFFER}>Buffer</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>queueFamilyIndices</code><br />
            An array of <Reference sectionID={SectionID.QUEUE}>Queue</Reference>
            family indices on which the buffer will be used.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
