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
    code={"#include <fillcan/shader/pipeline_layout.hpp>"}
/>

The <code>Pipeline Layout</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with a list of <Reference sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
    >descriptor set layouts</Reference
> and a list of <Reference sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
    >push constants</Reference
> and uses this information to construct a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayout.html"
    target="_blank">Vulkan Pipeline Layout</Anchor
> which can be used to bind multiple <Reference
    sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
> to a <Reference sectionID={SectionID.PIPELINE}>pipeline</Reference>.<br /><br
/>
Multiple descriptor set layouts can be used in a single <Reference
    sectionID={SectionID.PIPELINE}>pipeline</Reference
>. To group two or more descriptor sets into something that the <Reference
    sectionID={SectionID.PIPELINE}>pipeline</Reference
> can use, they must be merged into a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayout.html"
    target="_blank">Vulkan Pipeline Layout</Anchor
> object.
