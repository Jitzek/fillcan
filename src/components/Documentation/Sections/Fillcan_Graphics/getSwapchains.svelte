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
    code={`std::vector<Swapchain*> getSwapchains();`}
/>
<MethodDescription>
    <span slot="details">
        Get all the created <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchains</Anchor
        ></span
    >
    <span slot="return">
        A list of pointers to the created <Anchor
            href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
            >Swapchains</Anchor
        >.</span
    >
</MethodDescription>
