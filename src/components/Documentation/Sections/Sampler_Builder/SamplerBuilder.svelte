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
    code={"#include <fillcan/graphics/sampler_builder.hpp>"}
/>
The <code>Sampler Builder</code> class is part of the creational design pattern
to construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code=
{`LogicalDevice* pLogicalDevice = nullptr;
VkFilter magFilter = VK_FILTER_LINEAR;
VkFilter minFilter = VK_FILTER_LINEAR;
VkSamplerMipmapMode mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
VkSamplerAddressMode addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
VkSamplerAddressMode addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
VkSamplerAddressMode addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
float mipLodBias = 0.f;
VkBool32 anisotropyEnable = VK_FALSE;
float maxAnisotropy = 1.0f;
VkBool32 compareEnable = VK_FALSE;
VkCompareOp compareOp = VK_COMPARE_OP_ALWAYS;
float minLod = 0.f;
float maxLod = 0.f;
VkBorderColor borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
VkBool32 unnormalizedCoordinates = VK_FALSE;`}
/><br />
Example:
<Highlight language={cppHighlight} code=
{`fillcan::SamplerBuilder samplerBuilder = fillcan::SamplerBuilder();
samplerBuilder.setLogicalDevice(fillcan.getCurrentDevice());
samplerBuilder.setFilters(VK_FILTER_LINEAR, VK_FILTER_LINEAR);
samplerBuilder.setMipmapMode(VK_SAMPLER_MIPMAP_MODE_LINEAR);
samplerBuilder.setAddressModes(VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT);
samplerBuilder.setMipLodBias(0.0f);
samplerBuilder.setMaxAnisotropy(1.0f);
samplerBuilder.setCompareOp(VK_COMPARE_OP_ALWAYS);
samplerBuilder.setLod(0.0f, 0.0f);
samplerBuilder.setBorderColor(VK_BORDER_COLOR_INT_OPAQUE_BLACK);
std::unique_ptr<fillcan::Sampler> upSampler = samplerBuilder.getResult();`} />
