<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`unsigned int getLayers();`} />
<MethodDescription>
    <span slot="details"> Get the number of layers of the framebuffer. </span>
    <span slot="return"> The number of layers of the framebuffer. </span>
</MethodDescription>

<style lang="scss">
</style>
