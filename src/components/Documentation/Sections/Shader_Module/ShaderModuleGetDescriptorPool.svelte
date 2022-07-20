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
    code={`DescriptorPool* getDescriptorPool();`}
/>
<MethodDescription>
    <span slot="details">
        Get the <Reference sectionID={SectionID.DESCRIPTOR_POOL}
            >descriptor pool</Reference
        >.
    </span>
    <span slot="return">
        A pointer to the <Reference sectionID={SectionID.DESCRIPTOR_POOL}
            >descriptor pool</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
