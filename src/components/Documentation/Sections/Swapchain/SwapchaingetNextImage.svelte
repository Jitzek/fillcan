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
    code={`SwapchainImage getNextImage(Fence* pFence = nullptr);`}
/>
<MethodDescription>
    <span slot="details">
        Get the next available Swapchain <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.<br />
        The images of the Swapchain are not immediately usable. Before data can be
        written into it, the next available image must be obtained.</span
    >
    <div slot="params">
        <li>
            <code>pFence</code><br />
            A pointer to a <Reference sectionID={SectionID.FENCE}
                >Fence</Reference
            > which will be signaled once it's safe to render to the acquired <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            >.
        </li>
    </div>
    <span slot="return">
        A <Reference sectionID={SectionID.SWAPCHAIN_Swapchain_Image}>SwapchainImage</Reference>-struct containing the necessary information for
        rendering to the Swapchain Image.
    </span>
</MethodDescription>

<style lang="scss">
</style>
