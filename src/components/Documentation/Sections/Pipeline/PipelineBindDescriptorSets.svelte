<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void bindDescriptorSets();`} />
<MethodDescription>
    <span slot="details">
        bind all the <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor sets</Reference
        > defined within the <Reference sectionID={SectionID.SHADER_MODULE}
            >shader modules</Reference
        > of the <Reference sectionID={SectionID.PIPELINE_PIPELINE_SHADER_STAGE}
            >shader stages</Reference
        > to the bound <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        >.<br /><br />
        To access the resources associated with a <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        >, the <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > must be bound to the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        > that executes the commands that access those descriptors. There are two
        binding points for <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > — one for compute and one for graphics — these are the sets that can be
        accessed by the appropriate pipelines.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if the pipeline bindpoint is not set,
        this should be done by the class that extends the pipeline.<br />
        Also throws std::runtime_error if there is no command buffer bound.
    </span>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`void bindDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets, unsigned int firstSet);`}
/>
<MethodDescription>
    <span slot="details">
        bind the given <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor sets</Reference
        > to the bound <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        >.<br /><br />
        To access the resources associated with a <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        >, the <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > must be bound to the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        > that executes the commands that access those descriptors. There are two
        binding points for <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > — one for compute and one for graphics — these are the sets that can be
        accessed by the appropriate pipelines.
    </span>
    <div slot="params">
        <li>
            <code>pDescriptorSets</code><br />
            A list of pointers to the <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
            > to bind to the bound <Reference
                sectionID={SectionID.COMMAND_BUFFER}>command buffer</Reference
            >.
        </li>
        <li>
            <code>firstSet</code><br />
            The set number of the first <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
            > to bind. This is used to bind a subset of the sets accessible to the
            <Reference sectionID={SectionID.PIPELINE_LAYOUT}
                >pipeline layout</Reference
            >.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the pipeline bindpoint is not set,
        this should be done by the class that extends the pipeline.<br />
        Also throws std::runtime_error if there is no command buffer bound.
    </span>
</MethodDescription>

<Highlight
    language={cppHighlight}
    code={`void bindDescriptorSets(std::vector<std::string> names, unsigned int firstSet);`}
/>
<MethodDescription>
    <span slot="details">
        bind the given <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor sets</Reference
        > by name to the bound <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        >.<br /><br />
        To access the resources associated with a <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
        >, the <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > must be bound to the <Reference sectionID={SectionID.COMMAND_BUFFER}
            >command buffer</Reference
        > that executes the commands that access those descriptors. There are two
        binding points for <Reference sectionID={SectionID.DESCRIPTOR_SET}
            >descriptor set</Reference
        > — one for compute and one for graphics — these are the sets that can be
        accessed by the appropriate pipelines.
    </span>
    <div slot="params">
        <li>
            <code>names</code><br />
            A list of names of the <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
            > to bind to the bound <Reference
                sectionID={SectionID.COMMAND_BUFFER}>command buffer</Reference
            >.
        </li>
        <li>
            <code>firstSet</code><br />
            The set number of the first <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor set</Reference
            > to bind. This is used to bind a subset of the sets accessible to the
            <Reference sectionID={SectionID.PIPELINE_LAYOUT}
                >pipeline layout</Reference
            >.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the pipeline bindpoint is not set,
        this should be done by the class that extends the pipeline.<br />
        Also throws std::runtime_error if there is no command buffer bound.
    </span>
</MethodDescription>

<style lang="scss">
</style>
