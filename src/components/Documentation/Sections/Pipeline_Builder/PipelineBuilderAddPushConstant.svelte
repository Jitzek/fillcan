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
    code={`void addPushConstant(std::string name, VkPushConstantRange pushConstantRange);`}
/>
<MethodDescription>
    <span slot="details">
        Set the <Reference sectionID={SectionID.PIPELINE_LAYOUT_PUSH_CONSTANT}
            >push constants</Reference
        > for the pipeline.
    </span>
    <div slot="params">
        <li>
            <code>name</code><br />
            The identifying name for the push constant.
        </li>
        <li>
            <code>pushConstantRange</code><br />
            A <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPushConstantRange.html"
                target="_blank">VkPushConstantRange</Anchor
            >-structure defining the size and offset of the push constant.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
