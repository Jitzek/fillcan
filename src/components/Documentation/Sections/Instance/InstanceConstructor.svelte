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
    code={`Instance(
        std::string pApplicationName, 
        unsigned int applicationVersion, 
        std::vector<const char*> requiredLayers,
        std::vector<const char*> requiredExtensions\n);`}
/>
<MethodDescription>
    <span slot="details"> Create a new Instance. </span>
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
            <code>requiredLayers</code><br />
            The Instance layers that should be enabled. To get a list of supported
            layers the function <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceLayerProperties.html"
                target="_blank">vkEnumerateInstanceLayerProperties</Anchor
            > can be called.<br />
            Layers are used to intercept the Vulkan API and provide logging, profiling,
            debugging, and other additional features.<br />
            <Anchor href="{getState().URL.documentation}#{SectionID.FILLCAN}"
                >Fillcan</Anchor
            > and <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS}"
                >Fillcan Graphics</Anchor
            > will enable the layer <code>VK_LAYER_KHRONOS_validation</code> when
            the application is running in Debug mode.
        </li>
        <li>
            <code>requiredExtensions</code><br />
            The Instance extensions that should be enabled. To get a list of supported
            extensions the function <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html"
                target="_blank">vkEnumerateInstanceExtensionProperties</Anchor
            > can be called.<br />
            Vulkan requires applications to sign up for extensions and enable them
            explicitly. This allows drivers to disable extensions that are not in
            use and makes it more difficult for applications to accidentally use
            functionality that is part of an extension that they had no intention
            of enabling.
            <br />
            <Anchor href="{getState().URL.documentation}#{SectionID.FILLCAN}"
                >Fillcan</Anchor
            > and <Anchor
                href="{getState().URL
                    .documentation}#{SectionID.FILLCAN_GRAPHICS}"
                >Fillcan Graphics</Anchor
            > will enable the extension
            <code>VK_EXT_DEBUG_UTILS_EXTENSION_NAME</code> when the application is
            running in Debug mode.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
