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
    code={`std::vector<const char*> getRequiredExtensions();`}
/>
<MethodDescription>
    <span slot="details">
        Get a list of required extensions that should be enabled by Vulkan. The
        available extensions can be retrieved using <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html"
            target="_blank">vkEnumerateInstanceExtensionProperties()</Anchor
        >.
    </span>
    <span slot="return"> A list of the required extensions. </span>
</MethodDescription>

<style lang="scss">
</style>
