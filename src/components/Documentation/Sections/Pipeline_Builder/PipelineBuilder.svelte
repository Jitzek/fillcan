<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
    import glslHighlight from "svelte-highlight/languages/glsl";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/shader/pipeline_builder.hpp>"}
/>
The <code>Pipeline Builder</code> class is part of the creational design pattern
to construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`LogicalDevice* pLogicalDevice = nullptr;
VkPipelineCreateFlags flags = 0;
std::vector<PushConstant> pushConstants = {};
VkPipelineCache pipelineCache = VK_NULL_HANDLE;
Pipeline* pBasePipeline = nullptr;`}
/>