<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/buffer_view.hpp>"}
/>
The <code>Buffer View</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
>, a pointer to the parent <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
> which it will create a Buffer View of, along with information regarding the format
and size of the Buffer View.<br />
A Buffer View is used to interpret the data in a <Reference
    sectionID={SectionID.BUFFER}>Buffer</Reference
> with a specific format. Buffer Views represent a sub-scope of a buffer object.
Since the raw data in the <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
>
is then treated as a sequence of texels, this is also known as a texel buffer view.
A texel buffer view is directly accessible in shaders and Vulkan will automatically
convert the texels in the <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
> to the format expected by the shader.
