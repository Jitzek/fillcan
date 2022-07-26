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
    code={`void setDepthStencilState(PipelineDepthStencilState depthStencilState);`}
/>
<MethodDescription>
    <span slot="details">Set the Depth Stencil State.</span>
    <div slot="params">
        <li>
            <code>depthStencilState</code><br />
            The multisample state, this is a
            <code>PipelineDepthStencilState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineDepthStencilState {
    VkBool32 depthTestEnable = VK_TRUE;
    VkBool32 depthWriteEnable = VK_TRUE;
    VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
    VkBool32 depthBoundsTestEnable = VK_FALSE;
    VkBool32 stencilTestEnable = VK_FALSE;
    VkStencilOpState front = {};
    VkStencilOpState back = {};
    float minDepthBounds = 0.0f;
    float maxDepthBounds = 1.0f;
};`}
/>
<MethodDescription>
    <span slot="details">
        Describe the depth- stencil state.<br />
        The depth stencil state determines how the depth and stencil tests are performed
        and what happens to a snippet if it passes or fails one of these tests. The
        depth and stencil tests can be performed before or after the fragment shader
        has been run. By default, the tests take place after the fragment shader.
    </span>
    <div slot="params">
        <li>
            <code>depthTestEnable</code><br />
            Whether depth testing is enabled.
        </li>
        <li>
            <code>depthWriteEnable</code><br />
            Whether depth writing is enabled. Depth writes are always disabled when
            <code>depthTestEnable</code>
            is <code>VK_FALSE</code>.
        </li>
        <li>
            <code>depthCompareOp</code><br />
            The test to use. This is a member of the <VkReference
                reference="VkComareOp"
                version={1.3}>VkComareOp</VkReference
            >-enumerant.
        </li>
        <li>
            <code>depthBoundsTestEnable</code><br />
            Whether depth limits tests are enabled.
        </li>
        <li>
            <code>stencilTestEnable</code><br />
            Whether stencil testing is enabled.<br />
            If the depth test passes (or if the depth test is disabled), the snippet
            advances to the stencil test.
        </li>
        <li>
            <code>front</code><br />
            Determines the parameters of the stencil test. This is a member of the
            <VkReference reference="VkStencilOpState" version={1.3}
                >VkStencilOpState</VkReference
            >-enumerant.
        </li>
        <li>
            <code>back</code><br />
            Determines the parameters of the stencil test. This is a member of the
            <VkReference reference="VkStencilOpState" version={1.3}
                >VkStencilOpState</VkReference
            >-enumerant.
        </li>
        <li>
            <code>minDepthBounds</code><br />
            The minimum depth limit used in the depth limit test.
        </li>
        <li>
            <code>maxDepthBounds</code><br />
            The maximum depth limit used in the depth limit test.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
