<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/memory.hpp>"}
/>
The <code>Memory</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with a pointer to a <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
> or <Reference sectionID={SectionID.IMAGE}>Image</Reference> and required memory
properties and uses this information to allocate Memory for a given <Reference
    sectionID={SectionID.BUFFER}>Buffer</Reference
> or <Reference sectionID={SectionID.IMAGE}>Image</Reference>.<br />

Before a resource, such as a <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
> or <Reference sectionID={SectionID.IMAGE}>Image</Reference>, can be used by
Vulkan to store data, it must be associated with memory. A device memory
allocation is represented as a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDeviceMemory.html"
    target="_blank">VkDeviceMemory</Anchor
>-object.
