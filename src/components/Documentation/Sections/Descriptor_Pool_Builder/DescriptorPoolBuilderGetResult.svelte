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
    code={`std::unique_ptr<DescriptorPool> getResult(bool allocate = true);`}
/>
<MethodDescription>
    <span slot="details">
        Get the resulting <Reference sectionID={SectionID.DESCRIPTOR_POOL}
            >Descriptor Pool</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>allocate</code><br />
            Whether to automatically allocate the <Reference
                sectionID={SectionID.DESCRIPTOR_SET}>descriptor sets</Reference
            >.
        </li>
    </div>
    <span slot="return">
        A <Anchor
            href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
            target="_blank">unique pointer</Anchor
        > to the <Reference sectionID={SectionID.DESCRIPTOR_POOL}
            >Descriptor Pool</Reference
        >, it's ownership will be moved.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.DESCRIPTOR_POOL}>Descriptor Pool</Reference
        > couldn't be created. Also throws <code>std::runtime_error</code> if
        <code>allocate</code>
        is <code>true</code> and the <Reference
            sectionID={SectionID.DESCRIPTOR_SET}>Descriptor Set</Reference
        > failed to be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
