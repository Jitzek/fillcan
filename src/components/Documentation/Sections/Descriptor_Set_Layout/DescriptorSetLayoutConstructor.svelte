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
        Create a new Descriptor Set Layout.<br />
        It is recommended to not create a Descriptor Set Layout by it's Constructor,
        but to use a
        <Reference sectionID={SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER}
            >Descriptor Set Layout Builder</Reference
        > instead.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Descriptor Set Layout should be associated with.
        </li>
        <li>
            <code>bindings</code><br />
            A list of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayoutBinding.html"
                target="_blank">VkDescriptorSetLayoutBinding</Anchor
            >-structures.<br />
            Resources are bound by binding points in the descriptor set. Each member
            of the supplied list provides a description of a descriptor set layout
            binding.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderModule.html"
            target="_blank">Vulkan Descriptor Set Layout</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
