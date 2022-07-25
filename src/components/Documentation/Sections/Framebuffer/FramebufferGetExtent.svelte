<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`VkExtent2D getExtent();`} />
<MethodDescription>
    <span slot="details"> Get the extent of the framebuffer. </span>
    <span slot="return">
        The extent of the framebuffer, this is a <VkReference
            reference="VkExtent2D"
            version={1.3}>VkExtent2D</VkReference
        >-structure.
    </span>
</MethodDescription>

<style lang="scss">
</style>
