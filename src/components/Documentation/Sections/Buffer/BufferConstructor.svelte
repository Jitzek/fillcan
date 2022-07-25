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
    code={`Buffer(
    LogicalDevice* pLogicalDevice, 
    VkBufferCreateFlags& flags, 
    VkDeviceSize& size, 
    VkBufferUsageFlags& usage, 
    VkSharingMode& sharingMode,
    std::vector<uint32_t> queueFamilyIndices = {}\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Buffer.<br />
        It is recommended to not create a Buffer by it's Constructor, but to use
        a <Reference sectionID={SectionID.BUFFER_DIRECTOR}
            >Buffer Director</Reference
        > or <Reference sectionID={SectionID.BUFFER_BUILDER}
            >Buffer Builder</Reference
        > instead.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Buffer should be associated with.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCreateFlagBits.html"
                target="_blank">VkBufferCreateFlagBits</Anchor
            > which are all related to sparse buffers.<br />
            Sparse resources are not yet explicitly supported in Fillcan version
            {getState().Fillcan.version}.
        </li>
        <li>
            <code>size</code><br />
            The size of the Buffer, in bytes. (For example, 1MiB is
            <code>1024</code>
            * <code>1024</code>).
        </li>
        <li>
            <code>usage</code><br />
            A bitmask of members of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferUsageFlagBits.html"
                target="_blank">VkBufferUsageFlagBits</Anchor
            >-enumerant telling Vulkan how the Buffer will be used.
        </li>
        <li>
            <code>sharingMode</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html"
                target="_blank">VkSharingMode</Anchor
            >-enumerant indicating how the Buffer will be used in the multiple
            device <Reference sectionID={SectionID.QUEUE}>Queues</Reference> supported
            by the Device. Because Vulkan can run many commands in parallel, some
            implementations need to know whether the Buffer will essentially be used
            by a single command at a time or possibly by several. Setting
            <code>sharingMode</code>
            to <code>VK_SHARING_MODE_EXCLUSIVE</code> tells Vulkan that the
            Buffer will only be used for a single <Reference
                sectionID={SectionID.QUEUE}>Queue</Reference
            >, while setting
            <code>sharingMode</code>
            to
            <code>VK_SHARING_MODE_CONCURRENT</code> specifies that the
            application will use the Buffer on multiple <Reference
                sectionID={SectionID.QUEUE}>Queues</Reference
            > at once. Using
            <code>VK_SHARING_MODE_CONCURRENT</code> may result in lower
            performance on some systems, so unless necessary,
            <code>sharingMode</code>
            should be set to <code>VK_SHARING_MODE_EXCLUSIVE</code>.
        </li>
        <li>
            <code>queueFamilyIndices</code><br />
            An array of <Reference sectionID={SectionID.QUEUE}>Queue</Reference>
            family indices on which the buffer will be used.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <VkReference
            reference="VkBuffer"
            version={1.3}>Vulkan Buffer</VkReference
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
