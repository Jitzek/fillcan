<script lang="ts">
    export let href: string;
    export let target = "";
</script>

<a {href} {target}>
    <slot />
</a>

<style lang="scss">
    a {
        color: $--fg-color-accent-red;
        font-weight: bold;
        transition: all 0.25s;
        text-decoration: underline 2px;
    }

    a:hover,
    a:focus,
    a:active {
        color: $--fg-color-accent-blue;
    }
</style>
