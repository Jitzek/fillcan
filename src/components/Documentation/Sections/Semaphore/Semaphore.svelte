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
    code={"#include <fillcan/memory/semaphore.hpp>"}
/>
The <code>Semaphore</code> class takes in a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> uses this information to construct a new <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSemaphore.html"
    target="_blank">Vulkan Semaphroe</Anchor
><br />
A semaphore is a type of synchronization primitive that allows work performed by
different <Reference sectionID={SectionID.QUEUE}>queues</Reference> to be properly
planned and coordinated. Semaphores are used to manage the ownership of resources
in different <Reference sectionID={SectionID.QUEUE}>queues</Reference> on a single
device.
