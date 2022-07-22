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
    code={"#include <fillcan/shader/descriptor_pool_layout_builder.hpp>"}
/>
The <code>Descriptor Pool Builder</code> class is part of the creational design
pattern to construct complex objects step by step.<br />
The Builder pattern allows you to produce different types and representations of
an object using the same construction code.<br />
The builder has the following default values, these can be overridden by calling
their respective methods:
<Highlight
    language={cppHighlight}
    code={`struct DescriptorSetInfo {
    std::string name = "undefined";
    DescriptorSetLayout* pLayout = nullptr;
    std::vector<VkDescriptorPoolSize> poolSizes = {};
};
LogicalDevice* pLogicalDevice = nullptr;
VkDescriptorPoolCreateFlags flags = 0;
unsigned int maxSets = 0;
std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
std::vector<DescriptorSetInfo> descriptorSetInfos = {};`}
/><br />
Example:
<Highlight
    language={cppHighlight}
    code={`// Prepare some descriptor set layouts
...
fillcan::DescriptorSetLayout descriptorSetLayoutExample1 = descriptorSetLayoutBuilder.getResult();
descriptorSetLayoutBuilder.reset();
...
fillcan::DescriptorSetLayout descriptorSetLayoutExample2 = descriptorSetLayoutBuilder.getResult();
descriptorSetLayoutBuilder.reset();
...
fillcan::DescriptorSetLayout descriptorSetLayoutExample3 = descriptorSetLayoutBuilder.getResult();

// Create descriptor pool
fillcan::DescriptorPoolBuilder descriptorPoolBuilder{};

descriptorPoolBuilder.setLogicalDevice(fillcan.getCurrentDevice());

descriptorPoolBuilder.addSet(descriptorSetLayoutExample1, "DescriptorSetExample1");
descriptorPoolBuilder.addSet(descriptorSetLayoutExample2, "DescriptorSetExample2");
descriptorPoolBuilder.addSet(descriptorSetLayoutExample3, "DescriptorSetExample3");

fillcan::DescriptorPool descriptorPool = descriptorPoolBuilder.getResult();
`}
/>
