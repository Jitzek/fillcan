<script lang="ts">
    import type { SectionID } from "$objects/Documentation/Section";
    import { stateStore } from "$stores/StateStore";
    import Anchor from "./Anchor.svelte";

    export let sectionID: SectionID;
</script>

<Anchor href="{$stateStore.URL.documentation}#{sectionID}">
    <slot />
</Anchor>
