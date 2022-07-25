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
    code={`void addDependency(VkSubpassDependency dependencyDescription);`}
/>
<MethodDescription>
    <span slot="details">
        Add a subpass dependency.<br /><br />
        When there is more than one subpass in a render pass, Vulkan can figure out
        which subpasses are dependent on each other by following the attachment references
        and looking for inputs and outputs that make subpasses dependent on each
        other. However, there are cases where dependencies cannot be easily represented
        by a simple input-to-output relationship. This generally happens when a subpass
        writes directly to a resource, such as an image or buffer, and a subsequent
        subpass reads that data back. Vulkan cannot figure this out automatically,
        so it must explicitly indicate such dependency information.
    </span>
    <div slot="params">
        <li>
            <code>dependencyDescription</code><br />
            A <VkReference reference="VkSubpassDependency" version={1.3}
                >VkSubpassDependency</VkReference
            >-structure. The indices of both the source subpass and the
            destination subpass can be determined using the index return by <Reference
                sectionID={SectionID.RENDER_PASS_BUILDER_constructSubpass}
                >constructSubpass</Reference
            >.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
