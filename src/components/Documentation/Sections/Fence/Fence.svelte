<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/fence.hpp>"}
/>
The <code>Fence</code> class takes in a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> and a bitmask of optional flags and uses this information to construct a new <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkFence.html"
    target="_blank">Vulkan Fence</Anchor
> which it will wrap around to offer functionality such as: waiting for the fence
to be signaled and resetting the fence.<br />
A fence is a kind of synchronization primitive. Fences are used when the host has
to wait for the device to complete the execution of (large) pieces of work represented
by a submission, usually with the help of the operating system.
