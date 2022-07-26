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
    code={`void setInputAssemblyState(PipelineInputAssemblyState inputAssemblyState);`}
/>
<MethodDescription>
    <span slot="details">Set the Input Assembly State.</span>
    <div slot="params">
        <li>
            <code>inputAssemblyState</code><br />
            The input assembly state, this is a <code>PipelineInputAssemblyState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineInputAssemblyState {
    VkPrimitiveTopology topology;
    VkBool32 primitiveRestartEnable;
};`}
/>
<MethodDescription>
    <span slot="details"
        >Describe the input assembly state.<br />
        The input assembly stage reads the index and vertex buffers that contain
        information about the vertices making up the draw sent in the draw command.
    </span>
    <div slot="params">
        <li>
            <code>topology</code><br />
            The primitive topology. This is a member of the <VkReference
                reference="VkPrimitiveTopology"
                version={1.3}>VkPrimitiveTopology</VkReference
            >-enumeration.
        </li>
        <li>
            <code>primitiveRestartEnable</code><br />
            Used to restart primitive topologies of type "strip" and "fan". Requires
            an indexed draw.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
