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
    code={`std::vector<DescriptorSet*>& getDescriptorSets();`}
/>
<MethodDescription>
    <span slot="details">
        Get a <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > by name.
    </span>
    <div slot="params">
        <li>
            <code>name</code><br />
            The name of the <Reference sectionID={SectionID.DESCRIPTOR_SET}
                >descriptor set</Reference
            > to get.
        </li>
    </div>
    <span slot="return">
        The <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > with the given name, or <code>nullptr</code> if no <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        >
        with the given name was found.
    </span>
</MethodDescription>

<style lang="scss">
</style>
