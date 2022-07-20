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
    code={`DevicePool(
        Instance* pInstance, 
        Window* pWindow, 
        std::vector<const char*> requiredDeviceExtensions,
        VkPhysicalDeviceFeatures requiredDeviceFeatures\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Device Pool.<br />
        Initializes a list of <Anchor
            href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
            >Physical Devices</Anchor
        > that are supported for the purposes of the implementation.
    </span>
    <div slot="params">
        <li>
            <code>pInstance</code><br />
            A pointer to the <Anchor
                href="{getState().URL.documentation}#{SectionID.INSTANCE}"
                >Instance</Anchor
            > with which the <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.PHYSICAL_DEVICE}"
                >Physical Devices</Anchor
            > should be enumerated.
        </li>
        <li>
            <code>pWindow</code><br />
            If not <code>nullptr</code>, a pointer to the <Anchor
                href="{getState().URL.documentation}#{SectionID.WINDOW}"
                >Window</Anchor
            > with which the support for presentation will be determined for the
            <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.PHYSICAL_DEVICE}"
                >Physical Device</Anchor
            >.<br />
            Support for presentation- and graphics operations for the <Anchor
                href="{getState().URL.documentation}#{SectionID.QUEUE}"
                >Queues</Anchor
            > will be ensured as well.
        </li>
        <li>
            <code>requiredDeviceFeatures</code><br />
            The features a <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.PHYSICAL_DEVICE}"
                >Physical Device</Anchor
            > should have for the purposes of the application.<br />
            This should be a <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html"
                target="_blank">VkPhysicalDeviceFeatures</Anchor
            >-structure where each required feature should be set to true.
        </li>
        <li>
            <code>requiredDeviceExtensions</code><br />
            The extensions a <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.PHYSICAL_DEVICE}"
                >Physical Device</Anchor
            > should support for the purposes of the application.<br />
            This should be a list of strings containing the names of the extensions
            to support. The available extensions can be retrieved using <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html"
                target="_blank">vkEnumerateInstanceExtensionProperties()</Anchor
            >.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if no devices with Vulkan support were found.
    </span>
</MethodDescription>

<style lang="scss">
</style>
