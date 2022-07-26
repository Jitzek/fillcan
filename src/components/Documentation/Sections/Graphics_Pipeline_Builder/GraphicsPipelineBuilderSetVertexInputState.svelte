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
    code={`bool setVertexInputState(PipelineVertexInputState vertexInputState);`}
/>
<MethodDescription>
    <span slot="details">Set the Vertex Input State.</span>
    <div slot="params">
        <li>
            <code>vertexInputState</code><br />
            The vertex input state, this is a
            <code>PipelineVertexInputState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineVertexInputState {
    std::vector<VkVertexInputBindingDescription> vertexInputBindingDescriptions;
    std::vector<VkVertexInputAttributeDescription> vertexInputAttributeDescriptions;
};`}
/>
<MethodDescription>
    <span slot="details">
        Describe the vertex input state.<br />
        The vertex input stage inputs vertex-data into the vertex shader.
    </span>
    <div slot="params">
        <li>
            <code>vertexInputBindingDescriptions</code><br />
            Descriptions of the vertex-bindings. This is a list of <VkReference
                reference="VkVertexInputBindingDescription"
                version={1.3}>VkVertexInputBindingDescription</VkReference
            >-structures.
        </li>
        <li>
            <code>vertexInputAttributeDescriptions</code><br />
            Descriptions of the vertex-attributes. This is a list of <VkReference
                reference="VkVertexInputAttributeDescription"
                version={1.3}>VkVertexInputAttributeDescription</VkReference
            >-structures.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
