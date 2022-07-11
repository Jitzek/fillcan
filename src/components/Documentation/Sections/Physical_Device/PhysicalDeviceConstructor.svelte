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
    code={`PhysicalDevice(
        VkPhysicalDevice hPhysicalDevice, 
        Window* pWindow, 
        std::vector<const char*> requiredExtensions,
        VkPhysicalDeviceFeatures requiredFeatures = {}\n);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Physical Device.<br />
        Finds the queue family indices of the applicable <Anchor
            href="{getState().URL.documentation}#{SectionID.QUEUE}"
            >Queues</Anchor
        > (graphics, presentation and computation).
    </span>
    <div slot="params">
        <li>
            <code>hPhysicalDevice</code><br />
        </li>
        <li>
            <code>pWindow</code><br />
            If not <code>nullptr</code>, a pointer to the <Anchor
                href="{getState().URL.documentation}#{SectionID.WINDOW}"
                >Window</Anchor
            > with which the support for presentation can be determined and other
            surface related capabilities.<br />
            The queue family index for the graphics- and presentation <Anchor
                href="{getState().URL.documentation}#{SectionID.QUEUE}"
                >Queues</Anchor
            > will be looked for aswell.
        </li>
        <li>
            <code>requiredDeviceFeatures</code><br />
            The features the Physical Device should have for the purposes of the
            application.<br />
            This should be a <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html"
                target="_blank">VkPhysicalDeviceFeatures</Anchor
            >-structure where each required feature should be set to true.
        </li>
        <li>
            <code>requiredDeviceExtensions</code><br />
            The extensions the Physical Device should support for the purposes of
            the application.<br />
            This should be a list of strings containing the names of the extensions
            to support. The available extensions can be retrieved using <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html"
                target="_blank">vkEnumerateInstanceExtensionProperties()</Anchor
            >.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
