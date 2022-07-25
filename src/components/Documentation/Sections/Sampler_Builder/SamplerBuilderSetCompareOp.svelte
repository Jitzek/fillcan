<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import VkReference from "$components/Documentation/VkReference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`void setCompareOp(VkCompareOp compareOp);`}
/>
<MethodDescription>
    <span slot="details"
        >When a sampler is used with a depth image, it can be configured to
        perform a compare operation and return the result of the comparison
        instead of the raw values stored in the image. When this mode is
        enabled, the comparison is performed on each sample taken from the
        image, and the resulting value is the fraction of the total number of
        samples taken that passed the test. This can be used to implement a
        technique known as percentage closer filtering or PCF. This enables this
        mode.</span
    >
    <div slot="params">
        <li>
            <code>compareOp</code><br />
            A member of the <VkReference reference="VkCompareOp" version={1.3}
                >VkCompareOp</VkReference
            >-enumeration, which is used in many places in Vulkan, including the
            <Reference sectionID={SectionID.GRAPHICS_PIPELINE}
                >graphical pipeline</Reference
            >. This is the enumeration used to specify the depth test operation.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
