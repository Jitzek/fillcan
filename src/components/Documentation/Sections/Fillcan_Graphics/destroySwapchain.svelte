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
    code={`void destroySwapchain(unsigned int index = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Destroy a <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        > at a given index.</span
    >
    <div slot="params">
        <li>
            <code>index</code><br />
            The index of the <Anchor
                href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
                >Swapchain</Anchor
            > returned by <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS_createSwapchain}"
                >createSwapchain</Anchor
            > or <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS_recreateSwapchain}"
                >recreateSwapchain</Anchor
            > to destroy.
        </li>
    </div>
</MethodDescription>
