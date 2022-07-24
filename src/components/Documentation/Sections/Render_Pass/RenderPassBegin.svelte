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
    code={`void begin(
    CommandBuffer* pCommandBuffer, 
    Framebuffer* pFramebuffer, 
    std::vector<VkClearValue>* pClearValues = nullptr,
    VkRect2D* pRenderArea = nullptr
);`}
/>
<MethodDescription>
    <span slot="details">
        Prepare to render.<br />
        All drawings are in a render pass. While renderpass objects can encapsulate
        many subpasses, even a simple rendering that is included in a single output
        image must be part of a renderpass.
    </span>
    <div slot="params">
        <li>
            <code>pCommandBuffer</code><br />
            The <Reference sectionID={SectionID.COMMAND_BUFFER}
                >command buffer</Reference
            > that contains the commands specified in the render pass.
        </li>
        <li>
            <code>pFramebuffer</code><br />
            The <Reference sectionID={SectionID.FRAMEBUFFER}
                >framebuffer</Reference
            > in which to render. The <Reference
                sectionID={SectionID.FRAMEBUFFER}>framebuffer</Reference
            > is the collection of <Reference sectionID={SectionID.IMAGE}
                >images</Reference
            > rendered to by graphics commands.
        </li>
        <li>
            <code>pClearValues</code><br />
            A list of <VkReference reference="VkClearValue" version={1.3}
                >VkClearValue</VkReference
            >-unions. If one of the attachments in the render pass has a load of
            <code>VK_ATTACHMENT_LOAD_OP_CLEAR</code>, then the colors or values
            to which they are cleared are specified in this array.<br />
            The index of each attachment of the <code>attachments</code> field
            given in the constructor is used to index into the array of
            <VkReference reference="VkClearValue" version={1.3}
                >VkClearValue</VkReference
            >-unions. This means that if only some of the attachments have a
            load of <code>VK_ATTACHMENT_LOAD_OP_CLEAR</code>, there may be
            unused items in the array. There must be at least as many items in
            the <code>pClearValues</code> list as the highest indexed attachment
            with a load of <code>VK_ATTACHMENT_LOAD_OP_CLEAR</code>.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
