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
    code={`void transitionImageLayout(
    CommandBuffer* pCommandBuffer, 
    VkImageLayout oldLayout, 
    VkImageLayout newLayout, 
    VkAccessFlags srcAccessMask,
    VkAccessFlags dstAccessMask, 
    VkPipelineStageFlags srcStageMask, 
    VkPipelineStageFlags dstStageMask,
    VkDependencyFlags dependencyFlags = 0\n);`}
/>
<MethodDescription>
    <span slot="details"
        >Transition an Image from one layout to another using an <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageMemoryBarrier.html"
            target="_blank">Vulkan Image Memory Barrier</Anchor
        >.<br />
        Images are transferred from layout to layout using <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageMemoryBarrier.html"
            target="_blank">image memory barriers</Anchor
        >.<br />
        <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageMemoryBarrier.html"
            target="_blank">Image memory barriers</Anchor
        > are used to control access to an Image. They make our operations on the
        GPU happen in a certain order, which ensures that we get the expected result.
        A barrier separates two operations in a <Reference
            sectionID={SectionID.QUEUE}>Queue</Reference
        >: before the barrier and after the barrier. Work done before the
        barrier is completed is always done before it can be used again.</span
    >
    <div slot="params">
        <li>
            <code>pCommandBuffer</code><br />
            The <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffer</Reference
            > to use to transfer the Image layout.
        </li>
        <li>
            <code>oldLayout</code><br />
            The layout to be used before the barrier for the image. This is a member
            of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html"
                target="_blank">VkImageLayout</Anchor
            >-enumeration.
        </li>
        <li>
            <code>newLayout</code><br />
            The layout to use after the barrier for the image. This is a member of
            the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html"
                target="_blank">VkImageLayout</Anchor
            >-enumeration.
        </li>
        <li>
            <code>srcAccessMask</code><br />
            The access type of the source. This is a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAccessFlagBits.html"
                target="_blank">VkAccessFlagBits</Anchor
            >-enumeration.
        </li>
        <li>
            <code>dstAccessMask</code><br />
            The access type of the destination. This is a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAccessFlagBits.html"
                target="_blank">VkAccessFlagBits</Anchor
            >-enumeration.
        </li>
        <li>
            <code>srcStageMask</code><br />
            The access type of the resource. This is a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineStageFlagBits.html"
                target="_blank">VkPipelineStageFlagBits</Anchor
            >-enumeration.<br />
            The <code>srcStageMask</code> indicates when the source stage has
            finished reading or writing a source. As a result, moving that
            stage's effective position later in the pipeline doesn't change the
            fact that those accesses have been completed; it can only mean that
            the implementation is waiting longer than is really necessary to
            complete.<br />
            So it also waits for all phases of the pipeline before the specified
            phase.
        </li>
        <li>
            <code>dstStageMask</code><br />
            Which pipeline stages will read from the source. This is what happens
            after the barrier. Built from a number of members of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineStageFlagBits.html"
                target="_blank">VkPipelineStageFlagBits</Anchor
            >-enumeration.<br />
            The <code>dstStageMask</code> specifies the point at which the
            pipeline will wait before continuing. If an implementation moves
            that holdpoint before, it will still work. The event it's waiting
            for will still complete when the later parts of the pipeline run.
            That implementation simply misses the opportunity to perform work
            while it waited.<br />
            Later phases in the pipeline after the specified phase are therefore
            also blocked.
        </li>
        <li>
            <code>dependencyFlags</code><br />
            Specifies a set of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDependencyFlagBits.html"
                target="_blank">VkDependencyFlagBits</Anchor
            >-flags describing how the dependency represented by the barrier
            affects the resources referenced by the barrier.
        </li>
    </div>
    <span slot="return"
        >A pointer to the requested <Reference sectionID={SectionID.IMAGE_VIEW}
            >Image View</Reference
        >.
    </span>
    <span slot="note">
        It is usually better to use <Reference sectionID={SectionID.RENDER_PASS}
            >Render Passes</Reference
        > whenever possible for transferring Images from layout to layout.
    </span>
</MethodDescription>

<style lang="scss">
</style>
