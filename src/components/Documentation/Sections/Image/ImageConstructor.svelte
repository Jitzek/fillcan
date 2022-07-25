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
    code={`Image(
    LogicalDevice* pLogicalDevice, 
    VkImageCreateFlags flags, 
    VkImageType type, 
    VkFormat format, 
    VkExtent3D extent, 
    unsigned int mipLevels,
    unsigned int arrayLayers, 
    VkSampleCountFlagBits samples, 
    VkImageTiling tiling, 
    VkImageUsageFlags usage, 
    VkSharingMode sharingMode,
    std::vector<uint32_t>& queueFamilyIndices, 
    VkImageLayout initialLayout\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Image.<br />
        It is recommended to not create a Image by it's Constructor, but to use a
        <Reference sectionID={SectionID.IMAGE_DIRECTOR}
            >Image Director</Reference
        > or <Reference sectionID={SectionID.IMAGE_BUILDER}
            >Image Builder</Reference
        > instead.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Image should be associated with.
        </li>
        <li>
            <code>flags</code><br />
            A bitmask of <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageCreateFlagBits.html"
                target="_blank">VkImageCreateFlagBits</Anchor
            > that describe some properties of the image.
        </li>
        <li>
            <code>type</code><br />
            The type of image being created. The image type is essentially the dimensionality
            of the image and can be <code>VK_IMAGE_TYPE_1D</code>,
            <code>VK_IMAGE_TYPE_2D</code>
            or <code>VK_IMAGE_TYPE_3D</code>
            for a 1D, 2D or 3D image respectively.
        </li>
        <li>
            <code>format</code><br />
            Describes how texel data is stored in memory and interpreted by Vulkan.
        </li>
        <li>
            <code>extent</code><br />
            The size of the image in texels. This should be an instance of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkExtent3D.html"
                target="_blank">VkExtent3D</Anchor
            >
            structure , which has three members: <code>width</code>,
            <code>height</code>, and <code>depth</code>. These should be set
            respectively to the width, height and depth of the desired image.
            For 1D images, the height should be set to <code>1</code>, and for
            1D and 2D images, the depth should be set to <code>1</code>.
        </li>
        <li>
            <code>mipLevels</code><br />
            The number of mipmap levels to create in the image.
        </li>
        <li>
            <code>arrayLayers</code><br />
            The amount of images each mipmap level of the image has.
        </li>
        <li>
            <code>samples</code><br />
            The number of samples in the image. It must be a member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleCountFlagBits.html"
                target="_blank">VkSampleCountFlagBits</Anchor
            >-enumerant.
        </li>
        <li>
            <code>tiling</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageTiling.html"
                target="_blank">VkImageTiling</Anchor
            >-enumerant, which contains only <code>VK_IMAGE_TILING_LINEAR</code>
            or
            <code>VK_IMAGE_TILING_OPTIMAL</code>. Linear tiling means that image
            data is laid out from left to right, top to bottom, so that if the
            underlying memory is mapped and it is written with the CPU, it would
            form a linear image. Meanwhile, optimal tiling is an opaque display
            used by Vulkan to store data in memory to improve the efficiency of
            the memory subsystem on the device. This is generally what should be
            chosen unless the image needs to be CPU mapped and manipulated.
            Optimal tiling is likely to outperform linear tiling in most
            operations, and linear tiling may not be supported at all for some
            operations or formats, depending on the Vulkan implementation.
        </li>
        <li>
            <code>usage</code><br />
            A bitmask of members of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageUsageFlagBits.html"
                target="_blank">VkImageUsageFlagBits</Anchor
            >-enumerant telling Vulkan how the Image will be used.
        </li>
        <li>
            <code>sharingMode</code><br />
            A member of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html"
                target="_blank">VkSharingMode</Anchor
            >-enumerant indicating how the Image will be used in the multiple
            device <Reference sectionID={SectionID.QUEUE}>Queues</Reference> supported
            by the Device. Because Vulkan can run many commands in parallel, some
            implementations need to know whether the Image will essentially be used
            by a single command at a time or possibly by several. Setting
            <code>sharingMode</code>
            to <code>VK_SHARING_MODE_EXCLUSIVE</code> tells Vulkan that the
            Image will only be used for a single <Reference
                sectionID={SectionID.QUEUE}>Queue</Reference
            >, while setting
            <code>sharingMode</code>
            to
            <code>VK_SHARING_MODE_CONCURRENT</code> specifies that the
            application will use the Image on multiple <Reference
                sectionID={SectionID.QUEUE}>Queues</Reference
            > at once. Using
            <code>VK_SHARING_MODE_CONCURRENT</code> may result in lower
            performance on some systems, so unless necessary,
            <code>sharingMode</code>
            should be set to <code>VK_SHARING_MODE_EXCLUSIVE</code>.
        </li>
        <li>
            <code>queueFamilyIndices</code><br />
            A pointer to an array of <Reference sectionID={SectionID.QUEUE}
                >Queue</Reference
            > family indices on which the image will be used.
        </li>
        <li>
            <code>initialLayout</code><br />
            Images have a layout, which partially indicates how they will be used
            at a given time. This field determines the layout in which the image
            is created. The available layouts are the members of the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html"
                target="_blank">VkImageLayout</Anchor
            >-enumerant.<br />
            Images should initially be created in the format
            <code>VK_IMAGE_LAYOUT_UNDEFINED</code>
            or <code>VK_IMAGE_LAYOUT_PREINITIALIZED</code>.
            <code>VK_IMAGE_LAYOUT_PREINITIALIZED</code>
            should only be used if there is data in memory that is bound immediately
            to the image source.
            <code>VK_IMAGE_LAYOUT_UNDEFINED</code>
            should be used when moving the resource to another layout before use.
            Images can be moved out of the
            <code>VK_IMAGE_LAYOUT_UNDEFINED</code> layout at any time with little
            or no time cost.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <VkReference
            reference="VkImage"
            version={1.3}>Vulkan Image</VkReference
        > couldn't be created.
    </span>
</MethodDescription><br />

<Highlight
    language={cppHighlight}
    code={`Image(
    LogicalDevice* pLogicalDevice, 
    Swapchain* pSwapchain, 
    VkImage hImage\n);`}
/>
<MethodDescription>
    <span slot="details">
        Wrap around a <Reference sectionID={SectionID.SWAPCHAIN}
            >Swapchain</Reference
        > Image.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the <Reference sectionID={SectionID.SWAPCHAIN}
                >Swapchain</Reference
            > Image is associated with.
        </li>
        <li>
            <code>pSwapchain</code><br />
            A pointer to the <Reference sectionID={SectionID.SWAPCHAIN}
                >Swapchain</Reference
            > which owns the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImage.html"
                target="_blank">Vulkan Image</Anchor
            >.
        </li>
        <li>
            <code>hImage</code><br />
            The handle to the <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImage.html"
                target="_blank">Vulkan Image</Anchor
            > to wrap around.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImage.html"
            target="_blank">Vulkan Image</Anchor
        > couldn't be created.
    </span>
    <span slot="note"
        >This Constructor is primarily used by the Swapchain to create Image
        Views for it's images.<br />
        By using this Constructor most class members will have their default values.
    </span>
</MethodDescription>

<style lang="scss">
</style>
