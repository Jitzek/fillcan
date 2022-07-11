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
    code={`const std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const;`}
/>
<MethodDescription>
    <span slot="details">
        Query the properties of the <Reference sectionID={SectionID.QUEUE}
            >Queues</Reference
        > available on this Physical Device. >.
    </span>
    <span slot="return"
        >A list of <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkQueueFamilyProperties.html"
            target="_blank">VkQueueFamilyProperties</Anchor
        >-structures specifying the properties of the <Reference
            sectionID={SectionID.QUEUE}>Queues</Reference
        > available on this Physical Device.</span
    >
</MethodDescription>

<style lang="scss">
</style>
