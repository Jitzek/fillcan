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
    code={`Framebuffer(
    LogicalDevice* pLogicalDevice, 
    RenderPass* pRenderPass, 
    std::vector<ImageView*> pAttachments, 
    unsigned int width,
    unsigned int height, 
    unsigned int layers
);`}
/>
<MethodDescription>
    <span slot="details"> Create a new Framebuffer. </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Framebuffer should be associated with.
        </li>
        <li>
            <code>pRenderPass</code><br />
            A pointer to a <Reference sectionID={SectionID.RENDER_PASS}
                >render pass</Reference
            > that defines which <Reference sectionID={SectionID.RENDER_PASS}
                >render pass</Reference
            > the framebuffer will be compatible with. Two <Reference
                sectionID={SectionID.RENDER_PASS}>render passes</Reference
            > are compatible with the same framebuffer if their attachment references
            are the same.
        </li>
        <li>
            <code>pAttachments</code><br />
            The set of <Reference sectionID={SectionID.IMAGE}>images</Reference>
            to be bound into the framebuffer object. Each <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            >
            (/attachment) will be used as the corresponding attachment in the
            <code>attachments</code>
            list of the <Reference sectionID={SectionID.RENDER_PASS_Constructor}
                >Render Pass Constructor</Reference
            > of a <Reference sectionID={SectionID.RENDER_PASS}
                >render pass</Reference
            > instance.
        </li>
        <li>
            <code>width</code><br />
            The width of the framebuffer.
        </li>
        <li>
            <code>height</code><br />
            The height of the framebuffer.
        </li>
        <li>
            <code>layers</code><br />
            The number of layers of the framebuffer.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <VkReference
            reference="VkFramebuffer"
            version={1.3}>Vulkan Framebuffer</VkReference
        >
        couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
