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
    code={`void setMultisampleState(PipelineMultisampleState multisampleState);`}
/>
<MethodDescription>
    <span slot="details">Set the Multisample State.</span>
    <div slot="params">
        <li>
            <code>multisampleState</code><br />
            The multisample state, this is a
            <code>PipelineMultisampleState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineMultisampleState {
    VkSampleCountFlagBits rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    VkBool32 sampleShadingEnable = VK_FALSE;
    float minSampleShading = 1.0f;
    std::vector<VkSampleMask> sampleMask = {};
    VkBool32 alphaToCoverageEnable = VK_FALSE;
    VkBool32 alphaToOneEnable = VK_FALSE;
};`}
/>
<MethodDescription>
    <span slot="details">
        Describe the multisampling stage.<br />
        Multisampling is the process of generating multiple samples for each pixel
        in an image. It is used to counteract aliasing and can significantly improve
        image quality when used effectively.
    </span>
    <div slot="params">
        <li>
            <code>rasterizationSamples</code><br />
            Not yet researched. This is a member of <VkReference
                reference="VkSampleCountFlagBits"
                version={1.3}>VkSampleCountFlagBits</VkReference
            >.
        </li>
        <li>
            <code>sampleShadingEnable</code><br />
            Not yet researched.
        </li>
        <li>
            <code>minSampleShading</code><br />
            Not yet researched. This is a list of <VkReference
                reference="VkSampleMask"
                version={1.3}>VkSampleMask</VkReference
            >-structure.
        </li>
        <li>
            <code>sampleMask</code><br />
            Not yet researched.
        </li>
        <li>
            <code>alphaToCoverageEnable</code><br />
            Not yet researched.
        </li>
        <li>
            <code>alphaToOneEnable</code><br />
            Not yet researched.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
