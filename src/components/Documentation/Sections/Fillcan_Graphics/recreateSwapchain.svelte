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
    code={`unsigned int recreateSwapchain(uint32_t imageCount, VkPresentModeKHR presentMode, unsigned int index = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Recreate a <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        >.</span
    >
    <div slot="params">
        <li>
            <code>imageCount</code><br />
            The amount of <Reference sectionID={SectionID.IMAGE}
                >Images</Reference
            > the recreated <Anchor
                href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
                >Swapchain</Anchor
            > should have.
        </li>
        <li>
            <code>presentMode</code><br />
            The present mode of the recreated <Anchor
                href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
                >Swapchain</Anchor
            >. This should be member of the <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html"
                target="_blank">VkPresentModeKHR</Anchor
            >-struct
        </li>
        <li>
            <code>index</code><br />
            The index of the Swapchain returned by <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS_createSwapchain}"
                >createSwapchain</Anchor
            > or <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS_recreateSwapchain}"
                >recreateSwapchain</Anchor
            > to be recreated.
        </li>
    </div>
    <span slot="return">
        The index of the recreated <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        >.</span
    >
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.SWAPCHAIN}>Swapchain</Reference
        > couldn't be recreated.
    </span>
</MethodDescription><br />
<Highlight
    language={cppHighlight}
    code={`unsigned int recreateSwapchain(unsigned int index = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Recreate a <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        > using it's original values.</span
    >
    <div slot="params">
        <li>
            <code>index</code><br />
            The index of the Swapchain returned by <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS_createSwapchain}"
                >createSwapchain</Anchor
            > or <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS_recreateSwapchain}"
                >recreateSwapchain</Anchor
            > to be recreated.
        </li>
    </div>
    <span slot="return">
        The index of the recreated <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        >.</span
    >
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.SWAPCHAIN}>Swapchain</Reference
        > couldn't be recreated.
    </span>
</MethodDescription>
