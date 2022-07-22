<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`std::string DescriptorSet::getName() { return this->name; }`}
/>
<MethodDescription>
    <span slot="details">
        Get the identifying name of the descriptor set.
    </span>
    <span slot="return"> The identifying name of the descriptor set. </span>
</MethodDescription>

<style lang="scss">
</style>
