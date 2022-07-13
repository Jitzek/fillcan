<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`bool endAll();`} />
<MethodDescription>
    <span slot="details">
        Ends all <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        >.<br />
        Calls <Reference sectionID={SectionID.COMMAND_BUFFER_end}>end</Reference
        > on all <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        >.
    </span>
    <span slot="return">
        <code>true</code> if all <Reference sectionID={SectionID.COMMAND_BUFFER}
            >Command Buffers</Reference
        > were succesfully ended.
        <code>false</code> if not all <Reference
            sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
        > could be ended.
    </span>
</MethodDescription>

<style lang="scss">
</style>
