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
    code={`bool present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> waitSemaphores);`}
/>
<MethodDescription>
    <span slot="details">
        Present a Swapchain <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        > to the <Reference sectionID={SectionID.WINDOW}>Window</Reference> surface.
    </span>
    <div slot="params">
        <li>
            <code>pSwapchainImage</code><br />
            A pointer to the <Reference
                sectionID={SectionID.SWAPCHAIN_Swapchain_Image}
                >SwapchainImage</Reference
            >-structure containing the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > that should be presented.
        </li>
        <li>
            <code>waitSemaphores</code><br />
            The <Reference sectionID={SectionID.SEMAPHORE}>Semaphores</Reference
            > to wait for before presenting the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            >.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if the presentation was succesful. <code>false</code> if
        the presentation failed.
    </span>
</MethodDescription>

<style lang="scss">
</style>
