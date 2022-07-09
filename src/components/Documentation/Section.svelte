<script lang="ts">
    export let id = "undefined";
    export let label: string = "undefined";
    export let heading: 2 | 3 | 4 | 5;
    export let visible = false;

    let sectionElement: HTMLElement;

    let topOffsetInPx = 100;

    function window_handleScroll(_e: Event) {
        const rect = sectionElement?.getBoundingClientRect();
        visible =
            rect.top + rect.height >= topOffsetInPx &&
            rect.left >= topOffsetInPx &&
            rect.bottom - rect.height <=
                (window.innerHeight - topOffsetInPx ||
                    document.documentElement.clientHeight - topOffsetInPx) &&
            rect.right <=
                (window.innerWidth || document.documentElement.clientWidth);
    }
</script>

<svelte:window on:scroll={window_handleScroll} />

<section {id} bind:this={sectionElement}>
    {#if heading === 2}
        <h2>{label}</h2>
    {:else if heading === 3}
        <h3>{label}</h3>
    {:else if heading === 4}
        <h4>{label}</h4>
    {:else if heading === 5}
        <h5>{label}</h5>
    {/if}
    <slot />
</section>

<style lang="scss">
    h2,
    h3 {
        padding-top: 0;
    }

    h2,
    h3,
    h4,
    h5 {
        margin-bottom: 0.5rem;
    }
    h2 {
        font-size: 2.25rem;
    }
    h3 {
        font-size: 1.5rem;
    }
    h4 {
        font-size: 1.25rem;
    }
    h5 {
        font-size: 1.05rem;
    }
</style>
