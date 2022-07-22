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
    code={`void pushConstantData(
    CommandBuffer* pCommandBuffer, 
    std::string name, 
    std::unique_ptr<PushConstantData> upPushConstantData
);`}
/>
<MethodDescription>
    <span slot="details">
        Update the value of a <Reference
            sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
            >push constant</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>pCommandBuffer</code><br />
            A pointer to a <Reference sectionID={SectionID.COMMAND_BUFFER}
                >command buffer</Reference
            > to execute the update with.
        </li>
        <li>
            <code>name</code><br />
            The name of the <Reference
                sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
                >push constant</Reference
            > to update.
        </li>
        <li>
            <code>upPushConstantData</code><br />
            A <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointer</Anchor
            > to the new value of the <Reference
                sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
                >push constant</Reference
            >, please use <Anchor
                href="https://en.cppreference.com/w/cpp/utility/move"
                target="_blank">std::move</Anchor
            > to transfer ownership.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if no <Reference
            sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
            >push constant</Reference
        > with the requested <code>name</code> could be found.
    </span>
</MethodDescription>

<style lang="scss">
</style>
