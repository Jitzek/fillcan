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
    code={`DescriptorSet* allocateDescriptorSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name);`}
/>
<MethodDescription>
    <span slot="details">
        Allocate a single <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        >.<br />
        Assigns a block with descriptors from the pool by creating a new <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        >. The given <code>name</code> can be used as an identifier to retrieve
        and identify the allocated
        <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>pDescriptorSetLayout</code><br />
            A pointer to the <Reference
                sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
                >descriptor set layout</Reference
            > describing the <Reference sectionID={SectionID.DESCRIPTOR_SET}
                >descriptor set</Reference
            >.
        </li>
        <li>
            <code>name</code><br />
            The identifying name of the <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
            >.
        </li>
    </div>
    <span slot="return">
        A pointer to the created <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        >.</span
    >
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>Descriptor Set</Reference
        > failed to be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
