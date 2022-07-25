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
    code={"#include <fillcan/graphics/render_pass_builder.hpp>"}
/>
The <code>Render Pass Builder</code> class is part of the creational design
pattern to construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`LogicalDevice* pLogicalDevice = nullptr;
std::vector<VkAttachmentDescription> attachmentDescriptions = {};
std::vector<VkAttachmentReference> inputAttachments = {};
std::vector<VkAttachmentReference> colorAttachments = {};
std::unique_ptr<VkAttachmentReference> upDepthStencilAttachment = nullptr;
std::vector<uint32_t> preserveAttachments = {};
bool resolveCurrentBatch = false;
std::vector<VkSubpassDescription> subpassDescriptions = {};
std::vector<VkSubpassDependency> dependencyDescriptions = {};`}
/><br />
Example:
<Highlight
    language={cppHighlight}
    code={`fillcan::RenderPassBuilder renderPassBuilder = {};
renderPassBuilder.setLogicalDevice(fillcan.getCurrentDevice());

// Add attachment for subpass 1 describing the swapchain image
unsigned int swapChainAttachmentIndex = renderPassBuilder.addAttachment(
    {
        .flags = 0,
        .format = fillcan.getSwapchain()->getSurfaceFormat().format,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    }
);
// Add the attachment to the subpass 1 as a color attachment
renderPassBuilder.addColorAttachment(swapChainAttachmentIndex, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, false);

// Add attachment for subpass 1 describing the depth image
std::optional<VkFormat> depthImageFormat = fillcan.getCurrentDevice()->getPhysicalDevice()->findSupportedFormat(
    { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT }, 
    VK_IMAGE_TILING_OPTIMAL,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
);
if (!depthImageFormat.has_value()) {
    throw std::runtime_error("Failed to find a supported format for the depth image attachment.");
}
unsigned int depthImageAttachmentIndex = renderPassBuilder.addAttachment(
    {
        .flags = 0,
        .format = depthImageFormat.value(),
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    }
);
// Add the attachment to subpass 1 as a depthstencil attachment
renderPassBuilder.setDepthStencilAttachment(depthImageAttachmentIndex, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, false);

// Construct subpass 1, this will combine any attachments described before into a new subpass
unsigned int subpassIndex = renderPassBuilder.constructSubpass();

// Add a dependency for subpass 1 to make sure the subpass waits for the previous stages before executing
renderPassBuilder.addDependency(
    {
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = subpassIndex,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
    }
);

std::unique_ptr<fillcan::RenderPass> upRenderPass = renderPassBuilder.getResult();`}
/>
