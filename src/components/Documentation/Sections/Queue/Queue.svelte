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
    code={"Queue(LogicalDevice* pLogicalDevice, unsigned int queueFamilyIndex, unsigned int queueIndex);"}
/>

The <code>Queue</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with the queue family index and queue index and uses this information to
construct a <Reference sectionID={SectionID.COMMAND_POOL}
    >Command Pool</Reference
>.<br />
Each device in Vulkan has one or more Queues. The Queue is the part of the device
that does the actual work. It can be thought of as a sub-device that exposes a subset
of the functionality of the device.<br />
Queues are grouped into one or more queue families, each containing one or more Queues.
Queues within a single family are essentially identical. Their capabilities are the
same, their performance level and access to system resources is the same, and there
is no cost (other than synchronization) for transferring work between each other.<br
/>
The <Reference sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference> will
automatically attempt to create one graphics, presentation and computation Queue
which can be retrieved with <Reference
    sectionID={SectionID.LOGICAL_DEVICE_getGraphicsQueue}
    >getGraphicsQueue</Reference
>, <Reference sectionID={SectionID.LOGICAL_DEVICE_getPresentQueue}
    >getPresentQueue</Reference
> and <Reference sectionID={SectionID.LOGICAL_DEVICE_getComputeQueue}
    >getComputeQueue</Reference
>, respectively.
