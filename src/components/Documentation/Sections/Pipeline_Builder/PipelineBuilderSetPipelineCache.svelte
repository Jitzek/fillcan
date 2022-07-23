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
    code={`void setPipelineCache(VkPipelineCache pipelineCache);`}
/>
<MethodDescription>
    <span slot="details">
        Set the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html"
            target="_blank">pipeline cache</Anchor
        > for the pipeline.
    </span>
    <div slot="params">
        <li>
            <code>pipelineCache</code><br />
            A handle to a <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html"
                target="_blank">Vulkan Pipeline Cache</Anchor
            > object.<br />
            Allows the result of <Reference sectionID={SectionID.PIPELINE}
                >pipeline</Reference
            > construction to be reused between <Reference
                sectionID={SectionID.PIPELINE}>pipelines</Reference
            >
            and between runs of an application. Reuse between <Reference
                sectionID={SectionID.PIPELINE}>pipelines</Reference
            > is achieved by passing the same <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html"
                target="_blank">pipeline cache</Anchor
            > object when creating multiple related
            <Reference sectionID={SectionID.PIPELINE}>pipelines</Reference>.
            Reuse across runs of an application is achieved by retrieving
            <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html"
                target="_blank">pipeline cache</Anchor
            > contents in one run of an application, saving the contents, and using
            them to preinitialize a <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineCache.html"
                target="_blank">pipeline cache</Anchor
            > on a subsequent run.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
