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
    code={`void copy(
    VkDescriptorSetLayoutBinding srcDescriptorSetBinding, 
    DescriptorSet* pDstDescriptorSet,
    VkDescriptorSetLayoutBinding dstDescriptorSetBinding, 
    unsigned int dstArrayElement = 0, 
    unsigned int descriptorCount = 1\n);`}
/>
<MethodDescription>
    <span slot="details">
        Copy this descriptor set to another descriptor set.
    </span>
    <div slot="params">
        <li>
            <code>srcDescriptorSetBinding</code><br />
            The binding index of the descriptor within the set to copy from.
        </li>
        <li>
            <code>pDstDescriptorSet</code><br />
            A pointer to the descriptor set to copy to.
        </li>
        <li>
            <code>dstDescriptorSetBinding</code><br />
            The binding index of the descriptor within the set to copy to.
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
