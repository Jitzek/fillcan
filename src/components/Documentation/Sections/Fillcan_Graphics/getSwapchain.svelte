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
    code={`Swapchain* getSwapchain(unsigned int index = 0);`}
/>
<MethodDescription>
    <span slot="details">
        Get a <Anchor
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
            > to retrieve.
        </li>
    </div>
    <span slot="return">
        A pointer to the <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchain</Anchor
        > at the given index.</span
    >
</MethodDescription>
