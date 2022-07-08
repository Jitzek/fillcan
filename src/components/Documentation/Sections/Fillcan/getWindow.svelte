<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`Window* getWindow();`} />
<MethodDescription>
    <span slot="details">
        Get the <Anchor href="{getState().URL.documentation}#{SectionID.WINDOW}"
            >Window</Anchor
        ></span
    >
    <span slot="returns"
        >A pointer to the <Anchor
            href="{getState().URL.documentation}#{SectionID.WINDOW}"
            >Window</Anchor
        >.</span
    >
</MethodDescription>
