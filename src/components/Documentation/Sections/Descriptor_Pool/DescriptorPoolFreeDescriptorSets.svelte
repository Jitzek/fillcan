<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool freeDescriptorSets();`} />
<MethodDescription>
    <span slot="details">
        Free all the allocated <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor sets</Reference
        >.<br />
        If the descriptor pool was created with the <code>flags</code> field set
        to <code>VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT</code>,
        <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor sets</Reference
        > can be returned to the pool by freeing them.
    </span>
    <span slot="return">
        <code>true</code> if all the descriptor sets were succesfully freed.
        <code>false</code> if not all descriptor sets could be freed.</span
    >
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`bool freeDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets);`}
/>
<MethodDescription>
    <span slot="details">
        Free all the given allocated <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
        >.<br />
        If the descriptor pool was created with the <code>flags</code> field set
        to <code>VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT</code>,
        <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor sets</Reference
        > can be returned to the pool by freeing them.
    </span>
    <div slot="params">
        <li>
            <code>pDescriptorSets</code><br />
            A list of pointers to <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
            > to be freed.
        </li>
    </div>
    <span slot="return">
        <code>true</code> if all the descriptor sets were succesfully freed.
        <code>false</code> if not all descriptor sets could be freed.</span
    >
</MethodDescription>

<style lang="scss">
</style>
