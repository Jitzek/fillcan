<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`VkSurfaceKHR getSurface();`} />
<MethodDescription>
    <span slot="details">
        Get the <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceKHR.html"
            target="_blank">Vulkan Surface</Anchor
        > created with <Anchor
            href="{getState().URL
                .documentation}#{SectionID.WINDOW_createSurface}"
            >createSurface</Anchor
        >.
    </span>
    <span slot="return">
        A handle to the created <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceKHR.html"
            target="_blank">Vulkan Surface</Anchor
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
