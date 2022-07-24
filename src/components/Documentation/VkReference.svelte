<script lang="ts">
    import type { SectionID } from "$objects/Documentation/Section";
    import { stateStore } from "$stores/StateStore";
    import Anchor from "./Anchor.svelte";

    export let reference: string;
    export let version: number;
</script>

<Anchor
    href="https://registry.khronos.org/vulkan/specs/{version}-extensions/man/html/{reference}.html"
    target="_blank"
>
    <slot />
</Anchor>
