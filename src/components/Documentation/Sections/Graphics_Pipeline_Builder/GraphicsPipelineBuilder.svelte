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
    code={"#include <fillcan/graphics/graphics_pipeline_builder.hpp>"}
/>
The <code>Graphics Pipeline Builder</code> class extends the
<code>Pipeline Builder</code>
class and is part of the creational design pattern to construct complex objects step
by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`std::vector<PipelineShaderStage> shaderStages = {};
std::unique_ptr<PipelineVertexInputState> upVertexInputState = nullptr;
std::unique_ptr<PipelineInputAssemblyState> upInputAssemblyState = nullptr;
std::unique_ptr<PipelineTessellationState> upTessellationState = nullptr;
std::vector<std::unique_ptr<PipelineViewPortState>> upViewPortStates = {};
std::unique_ptr<PipelineRasterizationState> upRasterizationState = nullptr;
std::unique_ptr<PipelineMultisampleState> upMultisampleState = nullptr;
std::unique_ptr<PipelineDepthStencilState> upDepthStencilState = nullptr;
std::unique_ptr<PipelineColorBlendState> upColorBlendState = nullptr;
std::unique_ptr<PipelineDynamicState> upDynamicState = nullptr;
RenderPass* pRenderPass = nullptr;
unsigned int subpass = 0;`}
/><br />
Example:
<Highlight
    language={cppHighlight}
    code={`fillcan::GraphicsPipelineBuilder graphicsPipelineBuilder{};
graphicsPipelineBuilder.setLogicalDevice(fillcan.getCurrentDevice());
graphicsPipelineBuilder.addShaderStage(
    {
        .stage = VK_SHADER_STAGE_VERTEX_BIT, 
        .pShaderModule = pVertexShaderModule, 
        .name = "main"
    }
);
graphicsPipelineBuilder.addShaderStage({.stage = VK_SHADER_STAGE_FRAGMENT_BIT, .pShaderModule = pFragmentShaderModule, .name = "main"});

graphicsPipelineBuilder.addPushConstant(
    "SimplePushConstant",
    {
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 
        .offset = 0, 
        .size = sizeof(SimplePushConstantData)
    }
);

graphicsPipelineBuilder.setInputAssemblyState({.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, .primitiveRestartEnable = VK_FALSE});

// Describe the vertex shader
graphicsPipelineBuilder.setVertexInputState(
    {
        fillcan::Model::Vertex::getBindingDescriptions(),
        {
            fillcan::Model::Vertex::getPositionAttributeDescription(0), 
            fillcan::Model::Vertex::getColorAttributeDescription(1)
        }
    }
);

// The viewports and scissors are dynamic, but the amount of viewports and scissors should still be defined
std::vector<VkViewport> viewports = {};
viewports.resize(1);
std::vector<VkRect2D> scissors = {};
scissors.resize(1);
graphicsPipelineBuilder.addViewportState({viewports, scissors});

graphicsPipelineBuilder.setRasterizationState(
    {
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullmode = VK_CULL_MODE_NONE,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f
    }
);

graphicsPipelineBuilder.setMultisampleState(
    {
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable = VK_FALSE,
        .minSampleShading = 1.0f,
        .sampleMask = {},
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable = VK_FALSE
    }
);

// Enable z-testing
graphicsPipelineBuilder.setDepthStencilState(
    {
        .depthTestEnable = VK_TRUE,
        .depthWriteEnable = VK_TRUE,
        .depthCompareOp = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable = VK_FALSE,
        .front = {},
        .back = {},
        .minDepthBounds = 0.0f,
        .maxDepthBounds = 1.0f
    }
);

VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
colorBlendAttachment.blendEnable = VK_FALSE;
colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
colorBlendAttachment.colorWriteMask =
    VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments = {colorBlendAttachment};
graphicsPipelineBuilder.setColorBlendState(
    {
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachments = colorBlendAttachments,
        .blendConstants = std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}
    }
);

// Set the viewports and scissors to dynamic to allow for window resizing
std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
graphicsPipelineBuilder.setDynamicState({.dynamicStates = dynamicStates});
graphicsPipelineBuilder.setRenderPass(this->upRenderPass.get());

std::unique_ptr<fillcan::GraphicsPipeline> upGraphicsPipeline = graphicsPipelineBuilder.getResult();`}
/>
