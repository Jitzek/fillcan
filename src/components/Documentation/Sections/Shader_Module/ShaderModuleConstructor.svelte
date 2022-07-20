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
    code={`ShaderModule(
    LogicalDevice* pLogicalDevice, 
    std::vector<char>& code, 
    std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
    std::unique_ptr<DescriptorPool> upDescriptorPool\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Shader Module.<br />
        It is recommended to not create a Shader Module by it's Constructor, but
        to use
        <Reference sectionID={SectionID.FILLCAN_createShaderModule}
            >createShaderModule</Reference
        > instead.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > that owns the Shader Module.
        </li>
        <li>
            <code>code</code><br />
            The SPIR-V code.
        </li>
        <li>
            <code>upDescriptorSetLayouts</code><br />
            A list of <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointers</Anchor
            > to the <Reference sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
                >descriptor set layouts</Reference
            > describing the <Reference sectionID={SectionID.DESCRIPTOR_SET}
                >descriptor sets</Reference
            > that expose resources to the shader. Ownerships needs to be transferred
            using <Anchor
                href="https://en.cppreference.com/w/cpp/utility/move"
                target="_blank"><code>std::move</code></Anchor
            >.
        </li>
        <li>
            <code>upDescriptorPool</code><br />
            A <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointer</Anchor
            > to a <Reference sectionID={SectionID.DESCRIPTOR_POOL}
                >descriptor pool</Reference
            > from which the descriptor sets will be allocated. Ownership needs to
            be transferred using <Anchor
                href="https://en.cppreference.com/w/cpp/utility/move"
                target="_blank"><code>std::move</code></Anchor
            >.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderModule.html"
            target="_blank">Vulkan Shader Module</Anchor
        > couldn't be created.
    </span>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`ShaderModule(
    LogicalDevice* pLogicalDevice, 
    std::vector<uint32_t>& code, 
    std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
    std::unique_ptr<DescriptorPool> upDescriptorPool\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Shader Module.<br />
        It is recommended to not create a Shader Module by it's Constructor, but
        to use
        <Reference sectionID={SectionID.FILLCAN_createShaderModule}
            >createShaderModule</Reference
        > instead.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > that owns the Shader Module.
        </li>
        <li>
            <code>code</code><br />
            The SPIR-V code.
        </li>
        <li>
            <code>upDescriptorSetLayouts</code><br />
            A list of <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointers</Anchor
            > to the <Reference sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
                >descriptor set layouts</Reference
            > describing the <Reference sectionID={SectionID.DESCRIPTOR_SET}
                >descriptor sets</Reference
            > that expose resources to the shader. Ownerships needs to be transferred
            using <Anchor
                href="https://en.cppreference.com/w/cpp/utility/move"
                target="_blank"><code>std::move</code></Anchor
            >.
        </li>
        <li>
            <code>upDescriptorPool</code><br />
            A <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointer</Anchor
            > to a <Reference sectionID={SectionID.DESCRIPTOR_POOL}
                >descriptor pool</Reference
            > from which the descriptor sets will be allocated. Ownership needs to
            be transferred using <Anchor
                href="https://en.cppreference.com/w/cpp/utility/move"
                target="_blank"><code>std::move</code></Anchor
            >.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderModule.html"
            target="_blank">Vulkan Shader Module</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
