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

<Highlight language={cppHighlight} code={`void end();`} />
<MethodDescription>
    <span slot="details">
        Terminate the rendering in the render pass.<br />
        Once the render pass has started, drawing commands can be placed in the <Reference
            sectionID={SectionID.COMMAND_BUFFER}>command buffer</Reference
        >. All rendering is directed to the <Reference
            sectionID={SectionID.FRAMEBUFFER}>framebuffer</Reference
        > specified in the
        <code>framebuffer</code> field passed to <Reference
            sectionID={SectionID.RENDER_PASS_begin}>begin</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
