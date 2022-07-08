<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={"#include <fillcan/fillcan.hpp>"} />
The <code>Fillcan</code> class is the API through which the application can talk
with Vulkan.