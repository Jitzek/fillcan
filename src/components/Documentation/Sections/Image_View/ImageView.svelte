<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/image_view.hpp>"}
/>
The <code>Image View</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
>, a pointer to the parent <Reference sectionID={SectionID.IMAGE}
    >Image</Reference
> which it will create an Image View of, along with information regarding the view
type and format.<br />
In many cases, the <Reference sectionID={SectionID.IMAGE}>Image</Reference> resource
cannot be used directly because it requires more information than is contained in
the resource itself. For example, an <Reference sectionID={SectionID.IMAGE}
    >Image</Reference
> resource cannot be used directly as an attachment to a <Reference
    sectionID={SectionID.FRAMEBUFFER}>Framebuffer</Reference
> or bound in a <Reference sectionID={SectionID.DESCRIPTOR_SET}
    >Descriptor Set</Reference
> to be sampled in a shader. To meet these additional requirements, an image view
must be created, which is essentially a collection of properties and a reference
to a parent <Reference sectionID={SectionID.IMAGE}>Image</Reference> resource.
