<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/fillcan_graphics.hpp>"}
/>
Vulkan is primarily a graphics API in the sense that most of Vulkan's functionality
is devoted to image generation and processing. Most Vulkan applications are designed
to display their results to the user. This is a process known as presentation. Because
the variety of platforms that Vulkan runs on is large and because not all applications
need to present the output to the user visually, the presentation is not a core part
of the API, but is handled by a series of extensions. <br />
The <code>FillcanGraphics</code> class extends the <Anchor
    href="{getState().URL.documentation}#{SectionID.FILLCAN}"
    ><code>Fillcan</code></Anchor
> class to enable these extensions and offer functionality exclusive to the graphics
portion of Vulkan.
