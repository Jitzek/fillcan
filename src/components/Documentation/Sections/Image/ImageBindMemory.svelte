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
    code={`void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);`}
/>
<MethodDescription>
    <span slot="details"
        >Bind <Reference sectionID={SectionID.MEMORY}>Memory</Reference> to the Image.</span
    >
    <div slot="params">
        <li>
            <code>pMemory</code><br />
            A pointer to the <Reference sectionID={SectionID.MEMORY}
                >Memory</Reference
            > to bind to the Image.
        </li>
        <li>
            <code>memoryOffset</code><br />
            Specifies the offset in the <Reference sectionID={SectionID.MEMORY}
                >Memory</Reference
            > object the Image will live. If only one resource will be bound to
            the <Reference sectionID={SectionID.MEMORY}>Memory</Reference> object,
            this can be set to
            <code>0</code>.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
