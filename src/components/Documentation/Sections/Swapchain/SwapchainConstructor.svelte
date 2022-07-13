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
    code={`Swapchain(
        LogicalDevice* pLogicalDevice, 
        Window* pWindow, 
        Queue* pPresentQueue, 
        uint32_t imageCount = 3,
        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, 
        Swapchain* pOldSwapchain = nullptr\n);`}
/>
<MethodDescription>
    <span slot="details"> Create a new Swapchain. </span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > to associate the Swapchain with.
        </li>
        <li>
            <code>pWindow</code><br />
            A pointer to the <Reference sectionID={SectionID.WINDOW}
                >Window</Reference
            > whose surface the Swapchain should make presentable <Reference
                sectionID={SectionID.IMAGE}>Images</Reference
            > for.
        </li>
        <li>
            <code>pPresentQueue</code><br />
            The <Reference sectionID={SectionID.QUEUE}>Queue</Reference> which the
            Swapchain should use for presentation.
        </li>
        <li>
            <code>imageCount</code><br />
            The amount of <Reference sectionID={SectionID.IMAGE}
                >Images</Reference
            > the Swapchain should prepare.
        </li>
        <li>
            <code>presentMode</code><br />
            The presentation mode for the surface. This should be a member of the
            <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html"
                target="_blank">VkPresentModeKHR</Anchor
            >-enumerant.
        </li>
        <li>
            <code>pOldSwapchain</code><br />
            A pointer to the old Swapchain which can be used to return an existing
            Swapchain associated with the surface to Vulkan for recycling. This will
            be used when one Swapchain is replaced by another, such as when a Window
            is resized and the Swapchain needs to be remapped with larger images.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
