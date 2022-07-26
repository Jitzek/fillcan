<script lang="ts">
    import { base } from "$app/paths";

    import type { SectionID } from "$objects/Documentation/Section";
    import { stateStore } from "$stores/StateStore";
    import Anchor from "$components/Documentation/Anchor.svelte";

    export let sectionID: SectionID;
</script>

<Anchor href="{base}/documentation#{sectionID}">
    <slot />
</Anchor>
