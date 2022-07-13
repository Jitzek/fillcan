<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
    import Queue from "../Queue/Queue.svelte";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/graphics/swapchain.hpp>"}
/>
The <code>Swapchain</code> class takes in a pointer to the <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
>, the <Reference sectionID={SectionID.WINDOW}>Window</Reference> and the present
<Reference sectionID={SectionID.QUEUE}>Queue</Reference>. It uses this
information to prepare special image objects we can use to present to the <Reference
    sectionID={SectionID.WINDOW}>Window</Reference
> surface.<br /><br />
Swapchain objects are used to ask the window system to create one or more images
that can be used to present on a Vulkan surface (this is visible with the
<code>VK_KHR_surface</code>
extension). Each Swapchain object manages a series of <Reference
    sectionID={SectionID.IMAGE}>Images</Reference
>, usually in some form of a ring buffer. The application can ask the Swapchain
for the next available <Reference sectionID={SectionID.IMAGE}>Image</Reference>,
render to it, and then return the <Reference sectionID={SectionID.IMAGE}
    >Image</Reference
> to the swapchain ready for display. By managing presentable images in a ring or
queue, one <Reference sectionID={SectionID.IMAGE}>Image</Reference> can be displayed
on the screen while another is drawn to by the application, overlapping the operation
of the window system and the application.<br />
It is recommended to create Swapchains using <Reference
    sectionID={SectionID.FILLCAN_GRAPHICS_createSwapchain}
    >createSwapchain</Reference
>.
