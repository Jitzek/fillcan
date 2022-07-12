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
    code={`Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Queue.<br />
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Queue should be associated with.
        </li>
        <li>
            <code>queueFamilyIndex</code><br />
            The index of the chosen queue family.
        </li>
        <li>
            <code>queueIndex</code><br />
            The index of the chosen queue from the queue family.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
