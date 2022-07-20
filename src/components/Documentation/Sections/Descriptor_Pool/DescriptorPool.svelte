<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
    import glslHighlight from "svelte-highlight/languages/glsl";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/shader/descriptor_pool.hpp>"}
/>

The <code>Descriptor Pool</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with flags describing the supported operations and information about the
<Reference sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference> to be
allocated and uses this information to construct a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPool.html"
    target="_blank">Vulkan Descriptor Pool</Anchor
> from which it can allocate <Reference sectionID={SectionID.DESCRIPTOR_SET}
    >descriptor sets</Reference
>.<br /><br />
Resources are represented by descriptors and are bound to the pipeline by first binding
their descriptors into sets and then binding those descriptor sets to the pipeline.
This allows a large number of resources to be bound with very little processing time,
as the exact set of resources used by a particular drawing command can be predetermined
and the descriptor set containing them can be pre-created.<br />
The descriptors are allocated from descriptor pools. Descriptors for different types of resources are likely to
have similar data structures in a given implementation. Pooling the mappings used
to store descriptors allows drivers to make efficient use of memory.
