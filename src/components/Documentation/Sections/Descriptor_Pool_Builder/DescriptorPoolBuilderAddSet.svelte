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
    code={`void setFlags(VkDescriptorPoolCreateFlags flags);`}
/>
<MethodDescription>
    <span slot="details">
        Specify a set of descriptors of a certain type that should be
        allocatable from the pool.
    </span>
    <div slot="params">
        <li>
            <code>pDescriptorSetLayout</code><br />
            The <Reference sectionID={SectionID.DESCRIPTOR_SET_LAYOUT_BUILDER}
                >descriptor set layout</Reference
            > describing the order and types of resources in the set. Two sets with
            the same layout are considered compatible and interchangeable.
        </li>
        <li>
            <code>name</code><br />
            The identifying name of the <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
            >.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
