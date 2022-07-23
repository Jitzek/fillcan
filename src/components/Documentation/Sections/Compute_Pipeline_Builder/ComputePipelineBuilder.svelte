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
    code={"#include <fillcan/computing/compute_pipeline_builder.hpp>"}
/>
The <code>Command Pipeline Builder</code> class extends the
<code>Pipeline Builder</code>
class and is part of the creational design pattern to construct complex objects step
by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`PipelineShaderStage pipelineShaderStage = {};`}
/><br />
Example:
<Highlight
    language={cppHighlight}
    code={`// Create Shader Module
std::unique_ptr<fillcan::ShaderModule> upComputeShaderModule = fillcan.createShaderModule(...);

fillcan::ComputePipelineBuilder computePipelineBuilder{};
computePipelineBuilder.setLogicalDevice(fillcan.getCurrentDevice());
computePipelineBuilder.setFlags(0);
computePipelineBuilder.setBasePipeline(nullptr);

// Set the compute shader stage
computePipelineBuilder.setShaderStage({
    .stage = VK_SHADER_STAGE_COMPUTE_BIT,
    .pShaderModule = upComputeShaderModule.get(),
    .name = "main",
});

this->upComputePipeline = computePipelineBuilder.getResult();`}
/>
