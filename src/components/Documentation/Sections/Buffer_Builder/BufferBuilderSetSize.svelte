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
    code={`void setSize(VkDeviceSize size);`}
/>
<MethodDescription>
    <span slot="details">
        Set the size for the <Reference sectionID={SectionID.BUFFER}
            >Buffer</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>size</code><br />
            The size of the Buffer, in bytes. (For example, 1MiB is
            <code>1024</code>
            * <code>1024</code>).
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
