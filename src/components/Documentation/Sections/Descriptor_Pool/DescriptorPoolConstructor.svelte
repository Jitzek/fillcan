<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`DescriptorSetLayout(LogicalDevice* pLogicalDevice, std::vector<VkDescriptorSetLayoutBinding> bindings);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Descriptor Pool.<br />
        It is recommended to not create a Descriptor Pool by it's Constructor, but
        to use a
        <Reference sectionID={SectionID.DESCRIPTOR_POOL_BUILDER}
            >Descriptor Pool Builder</Reference
        > instead.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Descriptor Pool should be associated with.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPoolCreateFlagBits.html"
                target="_blank">VkDescriptorPoolCreateFlagBits</Anchor
            > that specify additional information about the allocation strategy to
            use to manage the resources consumed by the pool.
        </li>
        <li>
            <code>maxSets</code><br />
            The maximum total number of <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
            > that can be allocated from the pool.
        </li>
        <li>
            <code>poolSizes</code><br />
            A list of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPoolSize.html"
                target="_blank">VkDescriptorPoolSize</Anchor
            >-structures where each structure specifies the number of
            descriptors of a particular type that can be allocated from the
            pool.<br />
            If no element in the list specifies a particular type of resource, then
            no descriptors of that type can be allocated from the resulting pool. If
            a particular resource type appears twice in the array, the sum of all
            their
            <code>descriptorCount</code>
            fields (of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorPoolSize.html"
                target="_blank">VkDescriptorPoolSize</Anchor
            >-structure) is used to determine the pool for that resource type.
            The total number of resources in the pool is distributed across the
            sets allocated from the pool.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderModule.html"
            target="_blank">Vulkan Descriptor Pool</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
