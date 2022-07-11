<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/instance/device_pool.hpp>"}
/>
The <code>DevicePool</code> class takes in information about the <Anchor
    href="{getState().URL.documentation}#{SectionID.INSTANCE}">Instance</Anchor
>, <Anchor href="{getState().URL.documentation}#{SectionID.WINDOW}"
    >Window</Anchor
>, required device extensions and required device features and uses that
information to prepare a list of <Anchor
    href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
    >Physical Devices</Anchor
> that meet the stated requirements.<br />
These <Anchor href="{getState().URL.documentation}#{SectionID.PHYSICAL_DEVICE}"
    >Physical Devices</Anchor
> can be then be turned into <Anchor
    href="{getState().URL.documentation}#{SectionID.LOGICAL_DEVICE}"
    >Logical Devices</Anchor
> at the request of the application.<br />
The Device Pool is instantiated automatically by <Anchor
    href="{getState().URL.documentation}#{SectionID.FILLCAN}">Fillcan</Anchor
> and <Anchor href="{getState().URL.documentation}#{SectionID.FILLCAN_GRAPHICS}"
    >Fillcan Graphics</Anchor
>.
