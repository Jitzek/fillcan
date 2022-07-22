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
    code={`void writeTexelBufferView(
    VkDescriptorSetLayoutBinding binding, 
    BufferView* pTexelBufferView, 
    unsigned int dstArrayElement = 0,
    unsigned int descriptorCount = 1\n);`}
/>
<MethodDescription>
    <span slot="details">
        Bind a <Reference sectionID={SectionID.BUFFER_VIEW}
            >texel buffer view</Reference
        > to a given binding of the descriptor set.
    </span>
    <div slot="params">
        <li>
            <code>binding</code><br />
            The binding-index of the descriptor set the resource should be bound
            to.
        </li>
        <li>
            <code>pBufferView</code><br />
            A pointer to the <Reference sectionID={SectionID.BUFFER_VIEW}
                >texel buffer view</Reference
            > to be bound in the descriptor set.
        </li>
        <li>
            <code>dstArrayElement</code><br />
            If the binding in the set references an array of resources,
            <code>dstArrayElement</code>
            is used to specify the update start index. If the target binding is not
            an array, it should be set to <code>0</code>.
        </li>
        <li>
            <code>descriptorCount</code><br />
            Used to specify the number of consecutive descriptors, after the specified
            index in the <code>dstArrayElement</code> field, to be updated. If
            the target binding is not an array, it should be set to
            <code>1</code>.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
