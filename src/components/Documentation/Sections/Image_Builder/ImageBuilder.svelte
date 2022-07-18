<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/image_builder.hpp>"}
/>
The <code>Image Builder</code> class is part of the creational design pattern to
construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
It is recommended to use the <Reference sectionID={SectionID.IMAGE_DIRECTOR}
    >Image Director</Reference
> for creating <Reference sectionID={SectionID.IMAGE}>Images</Reference> unless the
director doesn't offer the required configuration.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`LogicalDevice* pLogicalDevice = nullptr;
VkImageCreateFlags flags = 0;
VkImageType type = VK_IMAGE_TYPE_2D;
VkFormat format = VK_FORMAT_R8G8B8A8_SRGB;
VkExtent3D extent = {1, 1, 1};
unsigned int mipLevels = 1;
unsigned int arrayLayers = 1;
VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
std::vector<uint32_t> queueFamilyIndices = {};
VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;`}
/>
