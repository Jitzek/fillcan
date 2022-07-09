<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`VkExtent2D getExtent();`} />
<MethodDescription>
    <span slot="details">
        Get the <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkExtent2D.html"
            target="_blank">Extent</Anchor
        > of the Window.
    </span>
    <span slot="return">
        The <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkExtent2D.html"
            target="_blank">Extent</Anchor
        > of the Window.
    </span>
</MethodDescription>

<style lang="scss">
</style>
