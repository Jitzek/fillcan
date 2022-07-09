<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`Fillcan(
        const char* pApplicationName, 
        uint32_t applicationVersion, 
        VkPhysicalDeviceFeatures requiredDeviceFeatures = {}, 
        std::vector<const char*> requiredDeviceExtensions = {}\n);`}
/>
<MethodDescription>
    <span slot="details">
        Intialize the Fillcan API.<br />
        Initializes <Anchor
            href="{getState().URL.documentation}#{SectionID.INSTANCE}"
            >Instance</Anchor
        > and <Anchor
            href="{getState().URL.documentation}#{SectionID.DEVICE_POOL}"
            >Device Pool</Anchor
        >.
    </span>
    <div slot="params">
        <li>
            <code>pApplicationName</code><br />
            The name of the application.
        </li>
        <li>
            <code>applicationVersion</code><br />
            The version of the application.
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
            > should enable for the purposes of the application.<br />
            This should be a list of strings containing the names of the extensions
            to enable. The available extensions can be retrieved using <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html"
                target="_blank">vkEnumerateInstanceExtensionProperties()</Anchor
            >. To be able to use a <Anchor
                href="{getState().URL.documentation}#{SectionID.SWAPCHAIN}"
                >Swapchain</Anchor
            > this list should contain
            <code>VK_KHR_SWAPCHAIN_EXTENSION_NAME</code> (<Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS}"
                >Fillcan Graphics</Anchor
            > contains this by default).<br />
        </li>
    </div>
</MethodDescription><br />
Example:
<Highlight
    language={cppHighlight}
    code={`fillcan::Fillcan fillcan = fillcan::Fillcan("Example Application", 1.0);`}
/>

<style lang="scss">
</style>
