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
    code={`Memory(
    LogicalDevice* pLogicalDevice, 
    Buffer* pBuffer, 
    VkMemoryPropertyFlags flags\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Memory allocation for a <Reference
            sectionID={SectionID.BUFFER}>Buffer</Reference
        >.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the Logical Device the Memory allocation should be associated
            with.
        </li>
        <li>
            <code>pBuffer</code><br />
            A pointer to the <Reference sectionID={SectionID.BUFFER}
                >Buffer</Reference
            > to create a Memory allocation for.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkMemoryPropertyFlagBits.html"
                target="_blank">VkMemoryPropertyFlagBits</Anchor
            > specifying the required properties for the Memory.
        </li>
    </div>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`Memory(
    LogicalDevice* pLogicalDevice, 
    Image* pImage, 
    VkMemoryPropertyFlags flags\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Memory allocation for an <Reference
            sectionID={SectionID.IMAGE}>Image</Reference
        >.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the Logical Device the Memory allocation should be associated
            with.
        </li>
        <li>
            <code>pBuffer</code><br />
            A pointer to the <Reference sectionID={SectionID.IMAGE}
                >Image</Reference
            > to create a Memory allocation for.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkMemoryPropertyFlagBits.html"
                target="_blank">VkMemoryPropertyFlagBits</Anchor
            > specifying the required properties for the Memory.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDeviceMemory.html"
            target="_blank">Vulkan Device Memory</Anchor
        > couldn't be created, the given <code>flags</code> are not supported or
        the memory requirements are not supported by the <Reference
            sectionID={SectionID.PHYSICAL_DEVICE}>Physical Device</Reference
        >.
    </span>
</MethodDescription>

<style lang="scss">
</style>
