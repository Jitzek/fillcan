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
    code={`std::unique_ptr<Image> make2DTexture(
    LogicalDevice* pLogicalDevice, 
    unsigned int width, 
    unsigned int height, 
    VkSampleCountFlagBits samples,
    VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE\n);`}
/>
<MethodDescription>
    <span slot="details">Create a new 2D texture.</span>
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            The <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the <Reference sectionID={SectionID.IMAGE}>Image</Reference> should
            be associated with.
        </li>
        <li>
            <code>width</code><br />
            The width the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > should have.
        </li>
        <li>
            <code>height</code><br />
            The height the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > should have.
        </li>
        <li>
            <code>samples</code><br />
            The sample count the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > should have.
        </li>
        <li>
            <code>sharingMode</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html"
                target="_blank">VkSharingMode</Anchor
            >-enumerant indicating how the <Reference
                sectionID={SectionID.IMAGE}>Image</Reference
            > will be used in the multiple device <Reference
                sectionID={SectionID.QUEUE}>Queues</Reference
            > supported by the Device.
        </li>
    </div>
    <span slot="return">
        A <Anchor
            href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
            target="_blank">unique pointer</Anchor
        > to the <Reference sectionID={SectionID.IMAGE}>Image</Reference>, it's
        ownership will be moved.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if a supported format could not be found.
        Also throws if the <Reference sectionID={SectionID.IMAGE}>Image</Reference> couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
