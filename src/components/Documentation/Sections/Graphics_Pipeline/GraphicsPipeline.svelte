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
    code={"#include <fillcan/graphics/graphics_pipeline.hpp>"}
/>

The <code>Graphics Pipeline</code> class extends the
<code><Reference sectionID={SectionID.PIPELINE}>Pipeline</Reference></code>
class.<br /><br />
Creating a graphics pipeline is accomplished using a method similar to that of creating
a <Reference sectionID={SectionID.COMPUTE_PIPELINE}>compute pipeline</Reference
>. However, the graphics pipeline contains many shader stages and fixed function
processing blocks, so the description of a graphics pipeline is much more
complex.<br /><br />
The most basic rendering will contain at least a vertex and a fragment shader. Each
shader stage can consume data from the previous stage or pass data to the next, forming
a pipeline. In some cases, the inputs to a shader are provided by fixed function
blocks, and sometimes the outputs of a shader are consumed by fixed function blocks.
Regardless of the source or destination of data, the way to declare the *input and
output to shaders is the same.<br /><br />
Example:<br /><br />

Vertex Shader:
<Highlight
    language={cppHighlight}
    code={`#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
        
layout(location = 0) out vec3 outColor;
        
layout(push_constant) uniform PushConstant {
    mat4 transform;
    vec3 color;
} push_constant;
        
void main() {
    gl_Position = push_constant.transform * vec4(inPosition, 1.0);
    outColor = inColor;
}`}
/>

Fragment Shader:
<Highlight
    language={glslHighlight}
    code={`#version 450

layout(location = 0) in vec3 inColor;
    
layout(location = 0) out vec4 outColor;
    
layout(push_constant) uniform PushConstant {
    mat4 transform;
    vec3 color;
} push_constant;
    
void main() {
    outColor = vec4(inColor, 1.0);
}`}
/>
<Highlight
    language={glslHighlight}
    code={`// Bind the pipeline to a command buffer
upGraphicsPipeline->bindToCommandBuffer(pCommandBuffer);

// Bind any descriptor sets to the pipeline
upGraphicsPipeline->bindDescriptorSets(std::vector<std::string>{"ExampleDescriptorSet"}, 0);

// Update any push constant data
upGraphicsPipeline->pushConstantData("ExamplePushConstant", std::move(examplePushConstantData));
`}
/>
C++ Code:
<Highlight
    language={cppHighlight}
    code={`struct SimplePushConstantData : public fillcan::PushConstantData {
    glm::mat4 transform{1.f};
    alignas(16) glm::vec3 color;
};
...
{
    // Create recording to gain access to a primary commandbuffer
    fillcan::CommandRecording* pGraphicsCommandRecording = fillcan.getCurrentDevice()->getGraphicsQueue()->createRecording(1, 0);
    fillcan::CommandBuffer* pGraphicsPrimaryCommandBuffer = pGraphicsCommandRecording->pPrimaryCommandBuffers.at(0);

    // Begin compute recording commands
    pGraphicsPrimaryCommandBuffer->begin();

    // Bind the pipeline to a command buffer
    upGraphicsPipeline->bindToCommandBuffer(pGraphicsPrimaryCommandBuffer);

    // Bind the descriptor sets to the bound command buffer
    upGraphicsPipeline->bindDescriptorSets();

    for (fillcan::GameObject& gameObject : gameObjects) {
        gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y + (0.5f * this->deltaTimef), glm::two_pi<float>());
        gameObject.transform.rotation.x = glm::mod(gameObject.transform.rotation.x + (0.25f * this->deltaTimef), glm::two_pi<float>());

        SimplePushConstantData data = {.transform = gameObject.transform.mat4(), .color = gameObject.color};
    
        // Update the push constant data
        std::unique_ptr<SimplePushConstantData> simplePushConstantData = std::make_unique<SimplePushConstantData>(data);
        upGraphicsPipeline->pushConstantData("SimplePushConstant", std::move(simplePushConstantData));

        gameObject.model->bind(pGraphicsPrimaryCommandBuffer);
        gameObject.model->drawIndexed();
    }

    // End the recording
    pGraphicsPrimaryCommandBuffer->end();
}`}
/>
