<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/memory/buffer_director.hpp>"}
/>
The <code>Buffer Director</code> class is part of the creational design pattern
to construct complex objects step by step.<br />
The director defines the order in which to execute building steps, while the
<Reference sectionID={SectionID.BUFFER_BUILDER}>builder</Reference> provides the
implementation for those steps.<br />
The Buffer Director defines methods for constructing frequently used <Reference
    sectionID={SectionID.BUFFER}>Buffer</Reference
> configurations. For it's methods it takes in the <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> with which the <Reference sectionID={SectionID.BUFFER}>Buffer</Reference> should
be associated with, the size of the <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
> and it's sharing mode, which will default to
<code>VK_SHARING_MODE_EXCLUSIVE</code> most of the time. With this information
it will use the <Reference sectionID={SectionID.BUFFER_BUILDER}
    >Buffer Builder</Reference
> to construct the requested <Reference sectionID={SectionID.BUFFER}
    >Buffer</Reference
> which it will then return as a <Anchor
    href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
    target="_blank">unique pointer</Anchor
> which ownership will be moved to the application.
