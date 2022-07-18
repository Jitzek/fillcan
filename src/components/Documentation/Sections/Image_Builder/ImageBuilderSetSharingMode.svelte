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
    code={`void setSharingMode(VkSharingMode sharingMode);`}
/>
<MethodDescription>
    <span slot="details">
        Set the sharing mode for the <Reference sectionID={SectionID.IMAGE}
            >Image</Reference
        >.
    </span>
    <div slot="params">
        <li>
            <code>sharingMode</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html"
                target="_blank">VkSharingMode</Anchor
            >-enumerant indicating how the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > will be used in the multiple device <Reference
                sectionID={SectionID.QUEUE}>Queues</Reference
            > supported by the Device. Because Vulkan can run many commands in parallel,
            some implementations need to know whether the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > will essentially be used by a single command at a time or possibly
            by several. Setting
            <code>sharingMode</code>
            to <code>VK_SHARING_MODE_EXCLUSIVE</code> tells Vulkan that the
            <Reference sectionID={SectionID.IMAGE}>Image</Reference> will only be
            used for a single <Reference sectionID={SectionID.QUEUE}
                >Queue</Reference
            >, while setting
            <code>sharingMode</code>
            to
            <code>VK_SHARING_MODE_CONCURRENT</code> specifies that the
            application will use the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > on multiple <Reference sectionID={SectionID.QUEUE}
                >Queues</Reference
            > at once. Using
            <code>VK_SHARING_MODE_CONCURRENT</code> may result in lower
            performance on some systems, so unless necessary,
            <code>sharingMode</code>
            should be set to <code>VK_SHARING_MODE_EXCLUSIVE</code>.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
