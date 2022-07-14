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
    code={`struct SwapchainImage {
    bool outOfDate;
    unsigned int index;
    ImageView* pSwapchainImageView;
    ImageView* pDepthImageView;
    Semaphore* pSemaphoreImageReady = nullptr;
    Semaphore* pSemaphorePresentReady = nullptr;
};`}
/>

The <code>Swapchain Image</code> structure is used by the Swapchain to keep
track of the information needed for rendering to and presenting of Swapchain
<Reference sectionID={SectionID.IMAGE}>Images</Reference>.
<MethodDescription>
    <span slot="params">
        <li>
            <code>outOfDate</code><br />
            Whether the Swapchain has become incompatible with the surface and can
            no longer be used for rendering. Usually happens after a <Reference
                sectionID={SectionID.WINDOW}>Window</Reference
            > resize.
        </li>
        <li>
            <code>index</code><br />
            The index of the Swapchain <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            >.
        </li>
        <li>
            <code>pSwapchainImageView</code><br />
            A pointer to the <Reference sectionID={SectionID.IMAGE_VIEW}
                >Image View</Reference
            > of the Swapchain <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            >.
        </li>
        <li>
            <code>pDepthImageView</code><br />
            A pointer to the Depth <Reference sectionID={SectionID.IMAGE_VIEW}
                >Image View</Reference
            > for the Swapchain <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            >.
        </li>
        <li>
            <code>pSemaphoreImageReady</code><br />
            A pointer to a <Reference sectionID={SectionID.SEMAPHORE}
                >Semaphore</Reference
            > which will be signaled once the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > can be rendered to.
        </li>
        <li>
            <code>pSemaphorePresentReady</code><br />
            A pointer to a <Reference sectionID={SectionID.SEMAPHORE}
                >Semaphore</Reference
            > which will be signaled once the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > can be presented.
        </li>
    </span>
</MethodDescription>
