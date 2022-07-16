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
    code={`BufferView(
    LogicalDevic pLogicalDevice, 
    Buffe pBuffer, 
    VkFormat format, 
    VkDeviceSize offset = 0, 
    VkDeviceSize range = VK_WHOLE_SIZE\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Buffer View.<br />
        It is recommended to not create a Buffer View by it's Constructor, but to
        use
        <Reference sectionID={SectionID.BUFFER_createBufferView}
            >createBufferView</Reference
        > instead.</span
    >
    <div slot="params">
        <li>
            <code>pLogicalDevice</code><br />
            A pointer to the <Reference sectionID={SectionID.LOGICAL_DEVICE}
                >Logical Device</Reference
            > the Buffer View should be associated with.
        </li>
        <li>
            <code>pBuffer</code><br />
            A pointer to the parent <Reference sectionID={SectionID.BUFFER}
                >Buffer</Reference
            > to create a Buffer View of.
        </li>
        <li>
            <code>format</code><br />
            When bound as a texel buffer, the data in the Buffer is interpreted as
            a string of texels with the format specified in this field.<br />
            The specified format must support
            <code>VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT</code>,
            <code>VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT</code> or
            <code>VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT</code>, as
            reported by <Reference
                sectionID={SectionID.PHYSICAL_DEVICE_getFormatProperties}
                >getFormatProperties</Reference
            >.
        </li>
        <li>
            <code>offset</code><br />
            The new view will be a "window" in the parent <Reference
                sectionID={SectionID.BUFFER}>Buffer</Reference
            >, starting from offset bytes.<br />
            The number of bytes of the <Reference sectionID={SectionID.BUFFER}
                >Buffer</Reference
            > where the Buffer View should start. To create a Buffer View of the
            entire <Reference sectionID={SectionID.BUFFER}>Buffer</Reference>,
            this must be <code>0</code>.
        </li>
        <li>
            <code>range</code><br />
            The new view will be a "window" in the parent <Reference
                sectionID={SectionID.BUFFER}>Buffer</Reference
            >, expanding to range bytes.<br />
            The number of bytes the Buffer View will contain from
            <code>offset</code>
            To create a Buffer View of the entire <Reference
                sectionID={SectionID.BUFFER}>Buffer</Reference
            >, it must be <code>VK_WHOLE_SIZE</code>.<br />
            The maximum number of texels that can be stored in a texel buffer is
            determined by inspecting the <code>maxTexelBufferElements</code>
            field of the <Reference sectionID={SectionID.PHYSICAL_DEVICE}
                >Physical Device</Reference
            >'s <Anchor
                href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceLimits.html"
                target="_blank">VkPhysicalDeviceLimits</Anchor
            >-structure, which can be retrieved by calling
            <Reference sectionID={SectionID.PHYSICAL_DEVICE_getProperties}
                >getProperties</Reference
            > If the
            <Reference sectionID={SectionID.BUFFER}>Buffer</Reference> is used as
            a texel buffer, the range divided by the size of a texel in format field
            must be less than or equal to this limit.
            <code>maxTexelBufferElements</code>
            is guaranteed to be a minimum of <code>65.536</code>, so if the view
            being created contains fewer texels, this limit does not need to be
            requested.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the <Anchor
            href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferView.html"
            target="_blank">Vulkan Buffer View</Anchor
        > couldn't be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
