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
    code={"#include <fillcan/instance/logical_device.hpp>"}
/>
The <code>Logical Device</code> class takes in a pointer to the <Reference
    sectionID={SectionID.PHYSICAL_DEVICE}>Physical Device</Reference
> to construct around. It uses the <Reference
    sectionID={SectionID.PHYSICAL_DEVICE}>Physical Device</Reference
> to construct the graphics, presentation and computation <Reference
    sectionID={SectionID.QUEUE}>Queues</Reference
> if available.<br />
The Logical Device is the software construction around a <Reference
    sectionID={SectionID.PHYSICAL_DEVICE}>Physical Device</Reference
>. A Logical Device represents a reservation of resources associated with a
particular <Reference sectionID={SectionID.PHYSICAL_DEVICE}
    >Physical Device</Reference
>. This includes a possible subset of the available <Reference
    sectionID={SectionID.QUEUE}>Queues</Reference
> on the <Reference sectionID={SectionID.PHYSICAL_DEVICE}
    >Physical Device</Reference
>, and it is the Logical Device that the application will communicate with most
of the time.
