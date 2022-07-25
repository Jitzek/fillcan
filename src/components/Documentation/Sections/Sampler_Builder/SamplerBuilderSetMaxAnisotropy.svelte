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
    code={`void setMaxAnisotropy(float maxAnisotropy);`}
/>
<MethodDescription>
    <span slot="details"
        >Set the max anisotropy if anisotropic filtering is to be used, also
        enables anisotropic filtering.</span
    >
    <div slot="params">
        <li>
            <code>maxAnisotropy</code><br />
            Because the number of samples taken can be quite large, anisotropic filtering
            can have a negative effect on performance. Also, in extreme cases, the
            projected footprint can be quite large, and this can result in a large
            area and a correspondingly blurry filter result. To mitigate these effects,
            the maximum amount of anisotropy can be locked by setting
            <code>maxAnisotropy</code>
            to a value between <code>1.0f</code> and the maximum value supported
            by the device. The maximum values can be determined by calling <Reference
                sectionID={SectionID.PHYSICAL_DEVICE_getProperties}
                >getProperties</Reference
            >
            and inspecting the <code>maxSamplerAnisotropy</code> member of the
            embedded <VkReference
                reference="VkPhysicalDeviceLimits"
                version={1.3}>VkPhysicalDeviceLimits</VkReference
            >
            structure.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
