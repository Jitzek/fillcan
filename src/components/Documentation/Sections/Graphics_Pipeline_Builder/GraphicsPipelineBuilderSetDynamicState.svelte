<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`void setDynamicState(PipelineDynamicState dynamicState);`}
/>
<MethodDescription>
    <span slot="details">Set the Dynamic State.</span>
    <div slot="params">
        <li>
            <code>dynamicState</code><br />
            The dynamic state, this is a PipelineDynamicState-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineDynamicState {
    std::vector<VkDynamicState> dynamicStates;
};`}
/>
<MethodDescription>
    <span slot="details">
        Describe the dynamic state.<br />
        To make fine-grained state changes more manageable, Vulkan provides the ability
        to mark certain parts of the graphics pipeline as dynamic, meaning they can
        be updated directly using commands directly in the command buffer rather
        than using an object. Since this reduces the chance for Vulkan to optimize
        or absorb parts of the state, it is necessary to specify exactly which state
        to make dynamically.
    </span>
    <div slot="params">
        <li>
            <code>dynamicStates</code><br />
            The states to make dynamic. This is a list of <VkReference
                reference="VkDynamicState"
                version={1.3}>VkDynamicState</VkReference
            >-structures.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
