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
    code={`void addColorAttachment(unsigned int attachmentDescriptionIndex, VkImageLayout layout, bool preserve);`}
/>
<MethodDescription>
    <span slot="details">
        Define a single color attachment, which is an attachment to which the
        output of the subpass is written.
    </span>
    <div slot="params">
        <li>
            <code>attachmentDescriptionIndex</code><br />
            The index of the attachment within the
            <code>attachmentDescriptions</code>-list. This index was returned
            when the attachment was added using <Reference
                sectionID={SectionID.RENDER_PASS_BUILDER_addAttachment}
                >addAttachment</Reference
            >.
        </li>
        <li>
            <code>layout</code><br />
            The image layout which the attachment is expected to be in within this
            subpass.
        </li>
        <li>
            <code>preserve</code><br />
            If there are attachments that should persist for the time in a subpass,
            but are not directly referenced by the subpass, they should be referenced
            as preserved. This reference prevents Vulkan from performing optimizations
            that could disrupt the content of those attachments.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
