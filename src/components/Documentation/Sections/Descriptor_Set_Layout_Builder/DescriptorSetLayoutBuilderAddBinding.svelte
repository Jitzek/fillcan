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
    code={`void addBinding(
    unsigned int binding, 
    VkDescriptorType descriptorType, 
    unsigned int descriptorCount, 
    VkShaderStageFlags stageFlags,
    std::vector<VkSampler> immutableSamplers = {}\n);`}
/>
<MethodDescription>
    <span slot="details">
        Add a <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayoutBinding.html"
            target="_blank">descriptor set layout binding</Anchor
        >. Resources are bound by binding points in the <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>binding</code><br />
            Each resource accessible to a shader is assigned a binding number. The
            bindings used in a <Reference sectionID={SectionID.DESCRIPTOR_SET}
                >descriptor set</Reference
            > do not have to be contiguous and there may be gaps (unused binding
            numbers) in a set. However, it is recommended that sparsely populated
            sets are not created as this can waste resources in the device.
        </li>
        <li>
            <code>descriptorType</code><br />
            The type descriptor on this binding point. This is a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorType.html"
                target="_blank">VkDescriptorType</Anchor
            >-enumerator.
        </li>
        <li>
            <code>descriptorCount</code><br />
            The number of descriptors in the binding, accessible in a shader as an
            array, unless <code>descriptorType</code> is
            <code>VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK</code>. In that case,
            <code>descriptorCount</code> is the size in bytes of the inline
            uniform block. If
            <code>descriptorCount</code> is <code>0</code>, this binding entry
            is reserved and the resource should not be accessed from any stage
            through this binding within a pipeline with the layout set.
        </li>
        <li>
            <code>stageFlags</code><br />
            A bitmask of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderStageFlagBits.html"
                target="_blank">VkShaderStageFlagBits</Anchor
            >-enumerant that specifies which pipeline shader stages can access a
            resource for this binding.
        </li>
        <li>
            <code>immutableSamplers</code><br />
            Affects <Reference sectionID={SectionID.SAMPLER}>sampler</Reference>
            initialization. If <code>descriptorType</code>
            specifies a
            <code>VK_DESCRIPTOR_TYPE_SAMPLER</code>
            or <code>VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER</code> type
            descriptor, then <code>pImmutableSamplers</code> can be used to
            initialize a set of immutable <Reference
                sectionID={SectionID.SAMPLER}>samplers</Reference
            >. Immutable <Reference sectionID={SectionID.SAMPLER}
                >samplers</Reference
            > are permanently embedded in the set layout and should not be modified;
            updating a
            <code>VK_DESCRIPTOR_TYPE_SAMPLER</code> descriptor with immutable
            <Reference sectionID={SectionID.SAMPLER}>samplers</Reference> is not
            allowed and updates of a
            <code>VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER</code>
            descriptor with immutable <Reference sectionID={SectionID.SAMPLER}
                >samplers</Reference
            > do not change the <Reference sectionID={SectionID.SAMPLER}
                >samplers</Reference
            > (the image views are updated, but the <Reference
                sectionID={SectionID.SAMPLER}>sampler</Reference
            > updates are ignored).
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
