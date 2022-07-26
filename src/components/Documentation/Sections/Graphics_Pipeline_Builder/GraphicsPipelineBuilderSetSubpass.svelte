<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`void setSubpass(unsigned int subpass);`}
/>
<MethodDescription>
    <span slot="details"
        >Set the subpass in the <Reference sectionID={SectionID.RENDER_PASS}
            >render pass</Reference
        > where this pipeline will be used.</span
    >
    <div slot="params">
        <li>
            <code>subpass</code><br />
            The index of the subpass in the <Reference
                sectionID={SectionID.RENDER_PASS}>render pass</Reference
            > where this pipeline will be used.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
