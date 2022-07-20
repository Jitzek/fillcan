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
    code={`const std::vector<VkDescriptorSetLayoutBinding>& getBindings() const;`}
/>
<MethodDescription>
    <span slot="details">
        Get a list of the Descriptor Set Layout Bindings..
    </span>
    <span slot="return"> A list of the Descriptor Set Layout Bindings.. </span>
</MethodDescription>

<style lang="scss">
</style>
