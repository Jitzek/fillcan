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
    code={`void destroyBufferView(unsigned int index);`}
/>
<MethodDescription>
    <span slot="details"
        >Destroy a <Reference sectionID={SectionID.BUFFER_VIEW}
            >Buffer View</Reference
        > by index.</span
    >
    <div slot="params">
        <li>
            <code>index</code><br />
            The index the <Reference sectionID={SectionID.BUFFER_VIEW}
                >Buffer View</Reference
            > to destroy.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
