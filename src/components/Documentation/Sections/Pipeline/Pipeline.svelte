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
    code={"#include <fillcan/shader/pipeline.hpp>"}
/>

The <code>Pipeline</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with flags controlling how the pipeline is created, a list of shader stages,
a list of push constants and a optionally pipeline cache and a base pipeline, and
uses this information to construct a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipeline.html"
    target="_blank">Vulkan Pipeline</Anchor
> and a <Reference sectionID={SectionID.PIPELINE_LAYOUT}
    >pipeline layout</Reference
> describing it's bound resources.<br /><br />
Before <Reference sectionID={SectionID.SHADER_MODULE}>shader modules</Reference>
can be used to do useful work on the device, you must create a pipeline. There are
two types of pipelines in Vulkan: "compute" and "graphics". The <Reference
    sectionID={SectionID.GRAPHICS_PIPELINE}>graphics pipeline</Reference
>
is quite complex and contains many phases that have nothing to do with shaders. However,
a <Reference sectionID={SectionID.COMPUTE_PIPELINE}>compute pipeline</Reference>
is conceptually much simpler and essentially contains nothing but just the shader
code.
