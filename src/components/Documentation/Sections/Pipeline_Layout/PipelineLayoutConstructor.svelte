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
    code={`PipelineLayout(
    LogicalDevice* pLogicalDevice, 
    std::vector<DescriptorSetLayout*>& pDescriptorSetLayouts,
    std::vector<PushConstant> pushConstants\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Pipeline Layout.<br />
        It is recommended to not create a Pipeline Layout by it's Constructor as
        a <Reference sectionID={SectionID.PIPELINE}>Pipeline</Reference> will create
        a Pipeline Layout as part of it's construction.
    </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Pipeline Layout should be associated with.
        </li>
        <li>
            <code>pDescriptorSetLayouts</code><br />
            A list of pointers to <Reference
                sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
                >descriptor set layouts</Reference
            > to be bound in the pipeline layout.
        </li>
        <li>
            <code>pushConstants</code><br />
            A list of <Reference
                sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
                >push constants</Reference
            > to be bound in the pipeline layout.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayout.html"
            target="_blank">Vulkan Pipeline Layout</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
