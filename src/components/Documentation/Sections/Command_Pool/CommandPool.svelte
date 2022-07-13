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
    code={"#include <fillcan/commands/command_pool.hpp>"}
/>

The <code>Command Pool</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with the queue family index uses this information to allocate, free and reset
<Reference sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference>.<br
/>
The primary purpose of a <Reference sectionID={SectionID.QUEUE}>Queue</Reference
> is to process work on behalf of the application. Work is represented as a series
of commands that are committed to <Reference
    sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
>. The application will create <Reference sectionID={SectionID.COMMAND_BUFFER}
    >Command Buffers</Reference
> with the work to be done and send them to one of the <Reference
    sectionID={SectionID.QUEUE}>Queues</Reference
> for execution. Before commands can be recorded, a <Reference
    sectionID={SectionID.COMMAND_BUFFER}>Command Buffer</Reference
> must be created. <Reference sectionID={SectionID.COMMAND_BUFFER}
    >Command Buffers</Reference
> themselves are not created directly, but allocated from Command Pools.
