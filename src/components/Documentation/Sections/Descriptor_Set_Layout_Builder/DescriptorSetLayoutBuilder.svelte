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
    code={"#include <fillcan/shader/descriptor_set_layout_builder.hpp>"}
/>
The <code>Descriptor Set Layout Builder</code> class is part of the creational
design pattern to construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`LogicalDevice* pLogicalDevice = nullptr;
std::vector<VkDescriptorSetLayoutBinding> bindings = {};`}
/><br />
Example:
<Highlight
    language={glslHighlight}
    code={`#version 450 core

layout (local_size_x=256, local_size_y=1, local_size_z=1) in;

layout (set=0, binding=0) uniform Config
{
    int transform;
    int integerCount;
} configData;

layout (set=0, binding=1) readonly buffer InputBuffer
{
    int integers[4096];
} inputData;

layout (set=0, binding=2) buffer OutputBuffer
{
    int integers[4096];
} outputData;

void main(void)
{
    // Grab global ID
    uint globalID = gl_GlobalInvocationID.x;

    // Don't access past the buffer size
    if (globalID < configData.integerCount)
    {
        // Perform some calculations
        outputData.integers[globalID] = inputData.integers[globalID] * configData.transform;
    }
}
`}
/>

<Highlight
    language={cppHighlight}
    code={`fillcan::DescriptorSetLayoutBuilder descriptorSetLayoutBuilder{};
descriptorSetLayoutBuilder.setLogicalDevice(fillcan.getCurrentDevice());

// Config
descriptorSetLayoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);

// InputBuffer
descriptorSetLayoutBuilder.addBinding(1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);

// OutputBuffer
descriptorSetLayoutBuilder.addBinding(2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT);

fillcan::DescriptorSetLayout descriptorSetLayout = descriptorSetLayoutBuilder.getResult();`}
/>
