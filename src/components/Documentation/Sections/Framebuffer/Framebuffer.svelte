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
    code={"#include <fillcan/graphics/framebuffer.hpp>"}
/>

The <code>Frambuffer</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
>, a pointer to a <Reference sectionID={SectionID.RENDER_PASS}
    >Render Pass</Reference
> along with lists of attachments, the width, the height and a number of array layers.
It uses this information to create a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFramebuffer.html"
    >Vulkan Framebuffer</Anchor
>.<br /><br />
A <Reference sectionID={SectionID.RENDER_PASS}>Render Pass</Reference> renders to
a Framebuffer. The framebuffer links to the <Reference
    sectionID={SectionID.IMAGE}>images</Reference
> being rendered to and is used when starting a <Reference
    sectionID={SectionID.RENDER_PASS}>render pass</Reference
> to set the target <Reference sectionID={SectionID.IMAGE}>images</Reference> for
rendering. Once the <Reference sectionID={SectionID.RENDER_PASS}
    >render pass</Reference
> is created, it can be used to create the framebuffers. Frame buffers are created
based on a particular <Reference sectionID={SectionID.RENDER_PASS}
    >render pass</Reference
> and they act as a link between the <Reference
    sectionID={SectionID.RENDER_PASS}>render pass</Reference
> attachments and the real <Reference sectionID={SectionID.IMAGE}
    >images</Reference
> to be rendered to.<br /><br />
The framebuffer is an object that represents the set of images into which <Reference
    sectionID={SectionID.GRAPHICS_PIPELINE}>graphics pipelines</Reference
> render. These affect the last few stages in the pipeline: depth- and stencil testing,
blending, logical operations, multisampling, and so on. A framebuffer object is created
by using a reference to a <Reference sectionID={SectionID.RENDER_PASS}
    >render pass</Reference
> and can be used with any render pass that has a similar arrangement of attachments.
