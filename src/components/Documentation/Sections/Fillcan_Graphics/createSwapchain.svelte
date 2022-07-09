<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`unsigned int createSwapchain(uint32_t imageCount = 3, VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR);`}
/>
<MethodDescription>
    <span slot="details">
        Create a <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        >.</span
    >
    <div slot="params">
        <li>
            <code>imageCount</code><br />
            The amount of images the <Anchor
                href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
                >Swapchain</Anchor
            > should have.
        </li>
        <li>
            <code>presentMode</code><br />
            The present mode of the <Anchor
                href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
                >Swapchain</Anchor
            >. This should be member of the <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html"
                target="_blank">VkPresentModeKHR</Anchor
            >-struct.
        </li>
    </div>
    <span slot="return">
        The index of the created <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        >.</span
    >
</MethodDescription>
