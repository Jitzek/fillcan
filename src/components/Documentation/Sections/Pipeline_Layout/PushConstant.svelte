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
    code={`struct PushConstantData {};

struct PushConstant {
    std::string name = "undefined";
    VkPushConstantRange range;
    std::unique_ptr<PushConstantData> upData = nullptr;
};`}
/>

The <code>Push Constant</code> structure is used by the Pipeline Layout to keep
track of the information needed for pushing data to push constants.<br />
The <code>Push Constant Data</code> structure can be extended and expanded with
any data the push constant should contain.<br /><br />
A push constant is a uniform variable in a shader that can be used just like a member
of a unified block, but instead of being backed up by memory, it's owned and updated
by Vulkan itself. As a result, new values for these constants can be pushed directly
into the pipeline from the command buffer, hence the term. Push constants become
part of the layout of the pipeline that will use them. When pipelined push constants,
they can consume some of the resources Vulkan would otherwise use to track pipeline
or descriptor bindings. Therefore, push constants should be considered relatively
precious resources.<br /><br />
It is recommended to not create the <code>Push Constant</code> structure
directly, but to add it to the Pipeline Layout using the <Reference
    sectionID={SectionID.PIPELINE_BUILDER}>Pipeline Layout Builder</Reference
>'s <Reference sectionID={SectionID.PIPELINE_BUILDER_addPushConstant}
    >addPushConstant</Reference
> method.
<MethodDescription>
    <span slot="params">
        <li>
            <code>name</code><br />
            The identifying name of the push constant. Can be used to push the data
            using <Reference
                sectionID={SectionID.PIPELINE_LAYOUT_pushConstantData}
                >pushConstantData</Reference
            >.
        </li>
        <li>
            <code>range</code><br />
            A <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPushConstantRange.html"
                target="_blank">VkPushConstantRange</Anchor
            >-structure defining the size and offset of the push constant.
        </li>
        <li>
            <code>upData</code><br />
            A <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointer</Anchor
            > to the <code>PushConstantData</code> defining the data of the push
            constant.
        </li>
    </span>
</MethodDescription>
