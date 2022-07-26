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
    code={`void setRasterizationState(PipelineRasterizationState rasterizationState);`}
/>
<MethodDescription>
    <span slot="details">Set the Rasterization State.</span>
    <div slot="params">
        <li>
            <code>rasterizationState</code><br />
            The rasterization state, this is a
            <code>PipelineRasterizationState</code>-structure.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`struct PipelineRasterizationState {
    VkBool32 depthClampEnable = VK_FALSE;
    VkBool32 rasterizerDiscardEnable = VK_FALSE;
    VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
    VkCullModeFlags cullmode = VK_CULL_MODE_NONE;
    VkFrontFace frontFace = VK_FRONT_FACE_CLOCKWISE;
    VkBool32 depthBiasEnable = VK_FALSE;
    float depthBiasConstantFactor = 0.0f;
    float depthBiasClamp = 0.0f;
    float depthBiasSlopeFactor = 0.0f;
    float lineWidth = 1.0f;
};`}
/>
<MethodDescription>
    <span slot="details">
        <br />
    </span>
    <div slot="params">
        <li>
            <code>depthClampEnable</code><br />
            Used to enable or disable depth clamping. This means that fragments that
            are outside the near and far planes are clamped instead of thrown out.
            This requires the
            <code>VkPipelineRasterizationDepthClipStateCreateInfoEXT</code>
            extension.
        </li>
        <li>
            <code>rasterizerDiscardEnable</code><br />
            Used to disable rasterization altogether. When this flag is set, the
            rasterizer will not run and no fragments will be produced.
        </li>
        <li>
            <code>polygonMode</code><br />
            Can be used to have Vulkan automatically turn triangles into points or
            lines. This a member of the <VkReference
                reference="VkPolygonMode"
                version={1.3}>VkPolygonMode</VkReference
            >-enumeration.
        </li>
        <li>
            <code>cullmode</code><br />
            Controls what parts of the input will be discarded. This is a bitmask
            of <VkReference reference="VkCullModeFlagBits" version={1.3}
                >VkCullModeFlagBits</VkReference
            >.
        </li>
        <li>
            <code>frontFace</code><br />
            Which direction a triangle faces is determined by the winding order of
            its vertice - whether they go clockwise or counterclockwise in the window
            space. This is a member of the <VkReference
                reference="VkFrontFace"
                version={1.3}>VkFrontFace</VkReference
            >-enumerant.
        </li>
        <li>
            <code>depthBiasEnable</code><br />
            This feature allows fragments to be depth compensated for before the
            depth test. This can be used to avoid depth fights.
        </li>
        <li>
            <code>depthBiasConstantFactor</code><br />
            A scalar factor that determines the constant depth value added to each
            clip.
        </li>
        <li>
            <code>depthBiasClamp</code><br />
            The maximum (or minimum) depth bias of a fragment.
        </li>
        <li>
            <code>depthBiasSlopeFactor</code><br />
            A scalar factor applied to the slope of a fragment in depth bias calculations.
        </li>
        <li>
            <code>lineWidth</code><br />
            The width of line primitives, in pixels. This applies to all lines gridded
            with the pipeline.<br />
            Some Vulkan implementations do not support broad strokes and may ignore
            this field. Others can work very slowly if this field is not
            <code>1.0f</code>; still others can fully respect this field and
            discard all lines if lineWidth is set to <code>0.0f</code>.
            Therefore, this field should always be set to <code>1.0f</code>,
            unless it is certain that it should be otherwise.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
