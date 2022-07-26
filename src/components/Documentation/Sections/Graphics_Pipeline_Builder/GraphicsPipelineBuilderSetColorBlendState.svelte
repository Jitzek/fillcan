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
    code={`void setColorBlendState(PipelineColorBlendState colorBlendState);`}
/>
<MethodDescription>
    <span slot="details">Set the Color Blend State.</span>
    <div slot="params">
        <li>
            <code>colorBlendState</code><br />
            The color blend state, this is a
            <code>PipelineColorBlendState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineColorBlendState {
    VkBool32 logicOpEnable = VK_FALSE;
    VkLogicOp logicOp = VK_LOGIC_OP_COPY;
    std::vector<VkPipelineColorBlendAttachmentState> attachments = {};
    std::array<float, 4> blendConstants = {};
};`}
/>
<MethodDescription>
    <span slot="details">
        Describe the color blend state.<br />
        The color operations take the final results of the fragment shader and postfragment
        operations and use them to update the <Reference
            sectionID={SectionID.FRAMEBUFFER}>framebuffer</Reference
        >. The color operations include blending and logic operations. This
        stage is responsible for writing fragments in the color attachments.
    </span>
    <div slot="params">
        <li>
            <code>logicOpEnable</code><br />
            Whether to perform logical operations between the fragment shader output
            and the contents of the color attachments.
        </li>
        <li>
            <code>logicOp</code><br />
            The logical operation to apply. This is a member of the <VkReference
                reference="VkLogicOp"
                version={1.3}>VkLogicOp</VkReference
            >-enumerant.
        </li>
        <li>
            <code>attachments</code><br />
            The color attachments to blend. This is a list of <VkReference
                reference="VkPipelineColorBlendAttachmentState"
                version={1.3}>VkPipelineColorBlendAttachmentState</VkReference
            >-structures.
        </li>
        <li>
            <code>blendConstants</code><br />
            A matrix of four values used as the R, G, B, and A components of the
            blending constant used in mixing, depending on the mixing factor.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
