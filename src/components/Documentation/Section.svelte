<script lang="ts">
    export let visible = false;
    export let topOffsetInPx: number = 0;

    let sectionElement: HTMLElement;

    function window_handleScroll(e: Event) {
        const rect = sectionElement?.getBoundingClientRect();
        visible =
            rect.top >= topOffsetInPx &&
            rect.left >= 0 &&
            rect.bottom <=
                (window.innerHeight - topOffsetInPx ||
                    document.documentElement.clientHeight - topOffsetInPx) &&
            rect.right <=
                (window.innerWidth || document.documentElement.clientWidth);
    }
</script>

<svelte:window on:scroll={window_handleScroll} />

<section bind:this={sectionElement}>
    <slot />
</section>

<style lang="scss">
</style>
