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
    code={`VkSharingMode getImageSharingMode();`}
/>
<MethodDescription>
    <span slot="details">
        Get the <Reference sectionID={SectionID.IMAGE}>Image</Reference> sharing
        mode describing how the Swapchain <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        > of this Swapchain can be accessed from <Reference
            sectionID={SectionID.QUEUE}>Queues</Reference
        >.</span
    >
    <span slot="return">
        A member of the <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html"
            target="_blank">VkSharingMode</Anchor
        >-enumerant describing the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        > sharing mode for the Swapchain <Reference sectionID={SectionID.IMAGE}
            >Images</Reference
        > of this Swapchain.
    </span>
</MethodDescription>

<style lang="scss">
</style>
