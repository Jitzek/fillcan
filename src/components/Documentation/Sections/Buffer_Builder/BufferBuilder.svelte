<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/buffer_builder.hpp>"}
/>
The <code>Buffer Builder</code> class is part of the creational design pattern
to construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
It is recommended to use the <Reference sectionID={SectionID.BUFFER_DIRECTOR}
    >Buffer Director</Reference
> for creating <Reference sectionID={SectionID.BUFFER}>Buffers</Reference> unless
the director doesn't offer the required configuration.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`LogicalDevice* pLogicalDevice = nullptr;
VkBufferCreateFlags flags = 0;
VkDeviceSize size = 0;
VkBufferUsageFlags usage = 0;
VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
std::vector<uint32_t> queueFamilyIndices = {};`}
/>
