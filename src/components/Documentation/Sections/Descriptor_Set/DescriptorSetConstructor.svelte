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
    code={`DescriptorSet(
    LogicalDevice* pLogicalDevice, 
    VkDescriptorSet hDescriptorSet, 
    DescriptorSetLayout* pDescriptorSetLayout\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Descriptor Set.<br />
        It is recommended to not create a Descriptor Set by it's Constructor, but
        to use
        <Reference sectionID={SectionID.DESCRIPTOR_POOL_allocateDescriptorSet}
            >allocateDescriptorSet</Reference
        > instead.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the descriptor set should be associated with.
        </li>
        <li>
            <code>pDescriptorPool</code><br />
            A pointer to the <Reference sectionID={SectionID.DESCRIPTOR_POOL}
                >descriptor pool</Reference
            > to allocate from.
        </li>
        <li>
            <code>pDescriptorSetLayout</code><br />
            A pointer to the <Reference
                sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
                >descriptor set layout</Reference
            > describing the bindings.
        </li>
        <li>
            <code>name</code><br />
            The identifying name of the descriptor set.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSet.html"
            target="_blank">Descriptor Set</Anchor
        > failed to be allocated.
    </span>
</MethodDescription>

<style lang="scss">
</style>
