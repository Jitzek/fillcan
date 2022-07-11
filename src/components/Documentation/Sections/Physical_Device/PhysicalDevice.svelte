<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/instance/physical_device.hpp>"}
/>
The <code>Physical Device</code> class takes in a handle to a <Anchor
    href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDevice.html"
    target="_blank">Vulkan Physical Device</Anchor
>, a pointer to the <Anchor
    href="{getState().URL.documentation}#{SectionID.WINDOW}">Window</Anchor
> (or <code>nullptr</code>) and the required device features and extensions.
<br />
With this information the <code>Physical Device</code> class acts as a wrapper
around the <Anchor
    href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDevice.html"
    target="_blank">Vulkan Physical Device</Anchor
> for requesting information about the Physical Device and it's capabilities.<br
/>
A <Anchor
    href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDevice.html"
    target="_blank">Vulkan Physical Device</Anchor
> usually represents a single piece of hardware or a collection of hardware that
is interconnected. There is a fixed, finite number of physical devices in any system,
unless that system supports reconfiguration, such as hot-plugging. Hot plugging is
the addition of a part to a running computer system without significant interruption
of system operation.
