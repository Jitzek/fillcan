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
    code={`const VkFormatProperties getFormatProperties(VkFormat format) const;`}
/>
<MethodDescription>
    <span slot="details">
        Query the properties of a given format for this Physical Device.
    </span>
    <div slot="params">
        <li>
            <code>format</code><br />
            The format of which to query it's properties for this Physical Device.
        </li>
    </div>
    <span slot="return">
        A <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkFormatProperties.html"
            target="_blank">VkFormatProperties</Anchor
        >-structure specifying the properties of the given format for this
        Physical Device.
    </span>
</MethodDescription>

<style lang="scss">
</style>
