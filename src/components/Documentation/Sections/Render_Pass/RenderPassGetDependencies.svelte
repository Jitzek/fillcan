<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`const std::vector<VkSubpassDependency>& getDependencies() const;`}
/>
<MethodDescription>
    <span slot="details">Get all the dependencies.</span>
    <span slot="return"
        >A list of <VkReference reference="VkSubpassDependency" version={1.3}
            >VkSubpassDependency</VkReference
        >-structures describing the dependencies.</span
    >
</MethodDescription>

<style lang="scss">
</style>
