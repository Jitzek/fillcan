<script lang="ts">
    import NavBar from "$components/NavBar/NavBar.svelte";
    import { DisplayType, State } from "$objects/State";
    import { stateStore } from "$stores/StateStore";

    let screenWidth: number;
    let screenHeight: number;

    $: {
        screenWidth, screenHeight;
        $stateStore.Screen.width = screenWidth;
        $stateStore.Screen.height = screenHeight;
        $stateStore.Screen.displayType =
            $stateStore.Screen.width <= 600
                ? DisplayType.MOBILE
                : DisplayType.DESKTOP;
    }
</script>

<svelte:window bind:innerWidth={screenWidth} bind:innerHeight={screenHeight} />

<div class="layout-wrapper">
    <NavBar />
    <slot />
</div>

<style lang="scss">
    :global(html),
    :global(body) {
        position: relative;
        margin: 0;
        height: 100%;
        background-color: $--bg-color-primary;
    }

    .layout-wrapper {
        height: 100%;
    }
</style>
