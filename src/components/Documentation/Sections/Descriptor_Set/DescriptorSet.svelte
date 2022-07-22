<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/shader/descriptor_set.hpp>"}
/>
The <code>Descriptor Set</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
>, a handle to the <Anchor href="" target="_blank">Vulkan Descriptor Set</Anchor
> which it will wrap around and the <Reference
    sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}>descriptor set layout</Reference
> which describes it's bindings<br />
The <code>Descriptor Set</code> class acts as a wrapper around the <Anchor
    href=""
    target="_blank">Vulkan Descriptor Set</Anchor
> for updating and copying it's contents.<br /><br />
A descriptor is a special opaque shader variable used by shaders to indirectly access
<Reference sectionID={SectionID.BUFFER}>buffer</Reference> and <Reference
    sectionID={SectionID.IMAGE}>image</Reference
> resources. It can be seen as a "pointer" to a resource. The Vulkan API allows these
variables to be changed between drawing operations so that the shaders have access
to different resources for each rendering. A descriptor set is called a "set" because
it can refer to a set of homogeneous resources that can be described with the same
layout binding.<br /><br />
A descriptor set is a set of resources tied to the <Reference
    sectionID={SectionID.PIPELINE}>pipeline</Reference
> as a group. Multiple sets can be tied to a <Reference
    sectionID={SectionID.PIPELINE}>pipeline</Reference
> at the same time. Each set has a <Reference
    sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}>layout</Reference
>, which describes the order and types of resources in the set. Two sets with
the same layout are considered compatible and interchangeable. The <Reference
    sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}>layout</Reference
> of the descriptor set is represented by an object and sets are created with respect
to this object. Furthermore, the set of sets accessible to a <Reference
    sectionID={SectionID.PIPELINE}>pipeline</Reference
> is grouped together in another object: the <Reference
    sectionID={SectionID.PIPELINE_LAYOUT}>pipeline layout</Reference
>. <Reference sectionID={SectionID.PIPELINE}>Pipelines</Reference> are created in
relation to this <Reference sectionID={SectionID.PIPELINE_LAYOUT}
    >pipeline layout</Reference
> object.
