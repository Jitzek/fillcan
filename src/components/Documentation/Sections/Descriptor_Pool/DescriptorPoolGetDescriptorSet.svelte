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
    code={`DescriptorSet* getDescriptorSet(std::string name);`}
/>
<MethodDescription>
    <span slot="details">
        Get an allocated <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > by name.</span
    >
    <div slot="params">
        <li>
            <code>name</code><br />
            The name of the <Reference sectionID={SectionID.DESCRIPTOR_SET}
                >descriptor set</Reference
            >.
        </li>
    </div>
    <span slot="return">
        A pointer to the requested <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        > or <code>nullptr</code> if no <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        > with the given name was found.</span
    >
</MethodDescription>

<style lang="scss">
</style>
