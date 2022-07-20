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
    code={`unsigned int createBufferView(VkFormat format, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);`}
/>
<MethodDescription>
    <span slot="details"
        >Create a <Reference sectionID={SectionID.BUFFER_VIEW}
            >Buffer View</Reference
        >.</span
    >
    <div slot="params">
        <li>
            <code>format</code><br />
            The format in which to interpret the Buffer.
        </li>
        <li>
            <code>offset</code><br />
            The <Reference sectionID={SectionID.BUFFER_VIEW}
                >Buffer View</Reference
            > will be a "window" into the parent buffer. The <code>offset</code>
            is the number of bytes within the Buffer where the <Reference
                sectionID={SectionID.BUFFER_VIEW}>Buffer View</Reference
            > should start. To create a <Reference
                sectionID={SectionID.BUFFER_VIEW}>Buffer View</Reference
            > of the entire Buffer, this must be 0.
        </li>
        <li>
            <code>range</code><br />
            The number of bytes the <Reference sectionID={SectionID.BUFFER_VIEW}
                >Buffer View</Reference
            > will contain from <code>offset</code>. To create a <Reference
                sectionID={SectionID.BUFFER_VIEW}>Buffer View</Reference
            > of the entire Buffer, this must be
            <code>VK_WHOLE_SIZE</code>.
        </li>
    </div>
    <span slot="return">
        The index of the newly created <Reference
            sectionID={SectionID.BUFFER_VIEW}>Buffer View</Reference
        >. This index can be used to get the created <Reference
            sectionID={SectionID.BUFFER_VIEW}>Buffer View</Reference
        > using <Reference sectionID={SectionID.BUFFER_getBufferView}
            >getBufferView</Reference
        >.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Reference
            sectionID={SectionID.BUFFER_VIEW}>Buffer View</Reference
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
