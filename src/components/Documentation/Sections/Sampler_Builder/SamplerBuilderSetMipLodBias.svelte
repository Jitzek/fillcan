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
    code={`void setMipLodBias(float mipLodBias);`}
/>
<MethodDescription>
    <span slot="details"> Set the bias for the mip Lod. </span>
    <div slot="params">
        <li>
            <code>mipLodBias</code><br />
            A floating-point bias that is added to the computed level of detail before
            making mipmap selection. This can push the level of detail up or down
            in the mipmap chain to make the resulting filtered texture look sharper
            or fainter than it would otherwise.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
