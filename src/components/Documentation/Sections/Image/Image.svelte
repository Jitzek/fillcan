<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/image.hpp>"}
/>
The <code>Image</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with a size and usage and uses this information to create a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImage.html"
    target="_blank">Vulkan Image Object</Anchor
> which it will wrap around to offer functionality such as: binding memory, creating
and destroying buffer views and copying data.<br />
<Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImage.html"
    target="_blank">Vulkan Images</Anchor
> represent linear arrays of data that are used for different purposes by binding
them to a <Reference sectionID={SectionID.GRAPHICS_PIPELINE}
    >Graphics Pipeline</Reference
> or <Reference sectionID={SectionID.COMPUTE_PIPELINE}
    >Compute Pipeline</Reference
> via <Reference sectionID={SectionID.DESCRIPTOR_SET}>Descriptor Sets</Reference
> or via certain commands, or by specifying them directly as parameters for certain
commands.
