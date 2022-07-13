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
    code={"#include <fillcan/commands/command_buffer.hpp>"}
/>

The <code>Command Buffer</code> class takes in a handle to a <Anchor
    href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBuffer.html"
    target="_blank">Vulkan Command Buffer</Anchor
> and the level of the Command Buffer.<br />
With this information the <code>Command Buffer</code> class acts as a wrapper
around the <Anchor
    href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkCommandBuffer.html"
    target="_blank">Vulkan Command Buffer</Anchor
> for beginning, ending and resetting the Command Buffer.<br />
All commands for the GPU are stored in a Command Buffer. All functions that perform
GPU work do nothing until the Command Buffer is sent to the GPU.<br />
Access to the Command Buffer must be synchronized externally, which means that it
is the responsibility of the application to ensure that no two threads simultaneously
try to insert commands into the same Command Buffer at the same time.<br />
However, the following is perfectly acceptable:
<ul>
    <li>
        One thread can record commands in multiple Command Buffers by simply
        calling Command Buffer functions sequentially on different Command
        Buffers.
    </li>
    <li>
        Two or more threads can participate in building a single Command Buffer,
        as long as the application can guarantee that no two of the threads ever
        run a Command Buffer build function simultaneously.
    </li>
</ul>
One of Vulkan's key design principles is to enable efficient multithreading. To achieve
this, it is important that the application threads do not block each other's execution.
For this reason, it is good practice to have one or more Command Buffers for each
thread rather than sharing one. Furthermore, since Command Buffers are allocated
from pools, one can go further by creating a <Reference
    sectionID={SectionID.COMMAND_POOL}>Command Pool</Reference
> for each thread, so that Command Buffers can be allocated by the worker threads
from their respective pools without these worker threads interacting with each other.
