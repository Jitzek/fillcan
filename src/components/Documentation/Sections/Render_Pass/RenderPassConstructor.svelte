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
    code={`RenderPass(
    LogicalDevice* pLogicalDevice, 
    std::vector<VkAttachmentDescription> attachments, 
    std::vector<VkSubpassDescription> subpasses,
    std::vector<VkSubpassDependency> dependencies
);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Render Pass.<br />
        It is recommended to not create a Render Pass by it's Constructor, but to
        use a <Reference sectionID={SectionID.RENDER_PASS_BUILDER}
            >Render Pass Builder</Reference
        > instead.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Render Pass should be associated with.
        </li>
        <li>
            <code>attachments</code><br />
            A list of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAttachmentDescription.html"
                target="_blank">VkAttachmentDescription</Anchor
            >-structures.<br />
            Each of these structures defines a single <Reference
                sectionID={SectionID.IMAGE}>image</Reference
            > to be used as input, output, or both within one or more of the subpasses
            in the render pass.
        </li>
        <li>
            <code>subpasses</code><br />
            A list of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSubpassDescription.html"
                target="_blank">VkSubpassDescription</Anchor
            >-structures.<br />
            Each of these structures defines a single subpass. Each subpass refers
            to a number of attachments (from the list given in the
            <code>attachments</code> field) as input or output.
        </li>
        <li>
            <code>dependencies</code><br />
            A list of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSubpassDependency.html"
                target="_blank">VkSubpassDependency</Anchor
            >-structures.<br />
            When there is more than one subpass in a render pass, Vulkan can figure
            out which subpasses are dependent on each other by following the attachment
            references and looking for inputs and outputs that make subpasses dependent
            on each other. However, there are cases where dependencies cannot be
            easily represented by a simple input-to-output relationship. This generally
            happens when a subpass writes directly to a resource, such as an image
            or buffer, and a subsequent subpass reads that data back. Vulkan cannot
            figure this out automatically, so it must explicitly indicate such dependency
            information.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <VkReference
            reference="VkRenderPass"
            version={1.3}>Vulkan Render Pass</VkReference
        >
        couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
