<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={"#include <fillcan/window.hpp>"} />
The <code>Window</code> class is used by <Anchor
    href="{getState().URL.documentation}#{SectionID.FILLCAN_GRAPHICS}"
    >Fillcan Graphics</Anchor
> for presentation. The Window is instantiated automatically by <Anchor
    href="{getState().URL.documentation}#{SectionID.FILLCAN_GRAPHICS}"
    >Fillcan Graphics</Anchor
>.