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
    code={`void setLogicalDevice(LogicalDevice* pLogicalDevice);`}
/>
<MethodDescription>
    <span slot="details">
        Set the <Reference sectionID={SectionID.LOGICAL_DEVICE}
            >Logical Device</Reference
        > for the <Reference sectionID={SectionID.RENDER_PASS}
            >Render Pass</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>attachmentDescription</code><br />
            A <VkReference reference="VkAttachmentDescription" version={1.3}
                >VkAttachmentDescription</VkReference
            >-structure. this structure defines a single image to be used as
            input, output, or both within one or more of the subpasses in the
            render pass.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
