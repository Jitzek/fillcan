<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/instance/instance.hpp>"}
/>
The <code>Instance</code> class is the connection between the application and
the Vulkan library and to create it some details of the application need to be
specified to the driver.<br />
The instance contains information such as an application name, name and version of
the engine used to create the application, and enabled instance-level extensions
and layers.<br />
Vulkan can be seen as a subsystem of the application. Once the application is linked
to the Vulkan libraries and initialized, a certain state is tracked. Vulkan does
not introduce a global state in the application, so all tracked state must be stored
in an object that the application provides, the <code>Instance</code> class.<br
/>
The Instance is instantiated automatically by <Anchor
    href="{getState().URL.documentation}#{SectionID.FILLCAN}">Fillcan</Anchor
> and <Anchor href="{getState().URL.documentation}#{SectionID.FILLCAN_GRAPHICS}"
    >Fillcan Graphics</Anchor
>.
