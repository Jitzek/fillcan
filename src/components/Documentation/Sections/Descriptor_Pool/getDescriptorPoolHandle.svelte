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
    code={`const VkDescriptorPool getDescriptorPoolHandle() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get the handle to the <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkDescriptorPool.html"
            target="_blank">Vulkan Descriptor Pool</Anchor
        >.
    </span>
    <span slot="return">
        The handle to the <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkDescriptorPool.html"
            target="_blank">Vulkan Descriptor Pool</Anchor
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
