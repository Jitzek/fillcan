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
    code={"#include <fillcan/graphics/render_pass.hpp>"}
/>

The <code>Render Pass</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with lists to attachments, the subpasses in which these attachments are used
and which attachments are dependent on eachother. It will use this information to
create a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkRenderPass.html"
    >Vulkan Render Pass</Anchor
> which it will wrap around to offer the ability to begin and end a rendering.<br
/><br />
One of the things that distinguishes a Vulkan <Reference
    sectionID={SectionID.GRAPHICS_PIPELINE}>graphics pipeline</Reference
> from a <Reference sectionID={SectionID.COMPUTE_PIPELINE}
    >compute pipeline</Reference
>
is that the <Reference sectionID={SectionID.GRAPHICS_PIPELINE}
    >graphics pipeline</Reference
> is usually used to convert pixels into images that can be further processed or
presented to the user. In complex graphics applications, the image is built over
many passes with each pass responsible for producing a different part of the scene,
applying full-frame effects such as post-processing or compositing, rendering user
interface elements, and so on. These passages can be rendered in Vulkan using a renderpass
object.<br /><br />
A single renderpass object spans multiple passes or render stages over a single set
of output images. Each pass within the render pass is known as a subpass. Renderpass
objects can contain many subpasses, but even in simple applications with only a single
pass over a single output image, the renderpass object contains information about
that output image.<br /><br />
All drawings must be in a render pass. Furthermore, <Reference
    sectionID={SectionID.GRAPHICS_PIPELINE}>graphics pipelines</Reference
> need to know where they are being rendered; therefore it is necessary to create
a renderpass object before creating a <Reference
    sectionID={SectionID.GRAPHICS_PIPELINE}>graphics pipeline</Reference
> so that the pipeline can be told about the images it will produce.
