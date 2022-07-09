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
    code={`Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                VkPhysicalDeviceFeatures requiredDeviceFeatures = {}, std::vector<const char*> requiredDeviceExtensions = {});`}
/>
<MethodDescription>
    <span slot="details">
        Intialize the Fillcan API.<br />
        Initializes the <Anchor
            href="{getState().URL.documentation}#{SectionID.WINDOW}"
            >Window</Anchor
        >, <Anchor href="{getState().URL.documentation}#{SectionID.INSTANCE}"
            >Instance</Anchor
        >, and <Anchor
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
            <code>windowWidth</code><br />
            The initial width the window.
        </li>
        <li>
            <code>windowHeight</code><br />
            The initial height the window.
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
</MethodDescription>
As of version {getState().Fillcan.version} the window can not be detached from the
application because the <Anchor
    href="{getState().URL.documentation}#{SectionID.INSTANCE}">Instance</Anchor
> might require certain extensions requested by the window and the <Anchor
    href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
    >Physical Device</Anchor
> requires a window to validate support for certain features.<br /><br />
Example:
<Highlight
    language={cppHighlight}
    code={`VkPhysicalDeviceFeatures requiredDeviceFeatures = {};\nrequiredDeviceFeatures.samplerAnisotropy = true;\nfillcan::Fillcan fillcan = fillcan::Fillcan(\"Example Application\", 1.0, 800, 600, requiredDeviceFeatures);`}
/>

<style lang="scss">
</style>
