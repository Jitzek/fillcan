<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/graphics/sampler.hpp>"}
/>
When shaders read from <Reference sectionID={SectionID.IMAGE}>images</Reference
>, they can do so in two ways. The first is to load the
<Reference sectionID={SectionID.IMAGE}>image</Reference> raw, which reads formatted
or unformatted data directly from a specific location in the image. The second way
is to sample the <Reference sectionID={SectionID.IMAGE}>image</Reference> using a
sampler. Sampling can include operations such as performing basic transformations
on the image-coordinates or filtering texels to smooth out the image-data returned
to the shader. The sampler is a separate object that provides an interface to extract
colors from a texture. It can be applied to any image be it 1D, 2D or 3D.<br
/>