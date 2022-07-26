<script lang="ts">
    import type { Section as SectionObject } from "$objects/Documentation/Section";
    import { stateStore } from "$stores/StateStore";

    export let sections: Array<SectionObject>;
    export let onReferenceClick: Function = () => {};

    let currentVisibleSection: SectionObject | null = null;
    let references: Array<HTMLElement> = [];
    let currentReference: HTMLElement | null = null;

    $: {
        sections;
        for (let i = 0; i < sections.length; i++) {
            if (sections[i].visible) {
                currentVisibleSection = sections[i];
                currentReference = references[i];
                break;
            }
        }
    }

    function scrollIntoViewIfNeeded(target: HTMLElement) {
        if (target.getBoundingClientRect().bottom > window.innerHeight) {
            target.scrollIntoView(false);
        }

        if (target.getBoundingClientRect().top < 100) {
            target.scrollIntoView();
        }
    }

    function window_handleScroll() {
        if (currentReference === null) return;
        scrollIntoViewIfNeeded(currentReference);
    }

    function handleReferenceClick(_e: MouseEvent) {
        onReferenceClick();
    }
</script>

<svelte:window on:scroll={window_handleScroll} />

<ul class="references-list">
    {#each sections as section, i}
        <li
            class="reference-item h{section.heading} {currentVisibleSection !==
                null && section.id === currentVisibleSection.id
                ? 'active'
                : ''}"
        >
            <a
                bind:this={references[i]}
                href="{$stateStore.URL.root}/documentation#{section.id}"
                on:click={handleReferenceClick}
            >
                {section.label}
                {#if currentVisibleSection !== null && section.id === currentVisibleSection.id}
                    <span class="visible-reference-indicator">{"<"}</span>
                {/if}
            </a>
        </li>
    {/each}
</ul>

<style lang="scss">
    .references-list {
        font-family: $--font-family-input;
        list-style: none;
        text-decoration: none;
        padding: 1.5rem 1.5rem 1.5rem 2.5rem;
        margin: 0;
        a {
            letter-spacing: 0.025rem;
            text-decoration: none;
        }
        .reference-item.h2 {
            margin-top: 1rem;
            a {
                color: $--input-fg-color-primary;
                text-transform: uppercase;
                font-size: 1.2rem;
            }
        }
        .reference-item.h3 {
            a {
                color: $--input-fg-color-secondary;
                padding-left: 1rem;
                font-size: 1.1rem;
            }
        }
        .reference-item.h4 {
            a {
                color: $--input-fg-color-secondary;
                padding-left: 2rem;
                font-size: 1.05rem;
            }
        }
        .reference-item.h5 {
            a {
                color: $--input-fg-color-secondary;
                padding-left: 3rem;
                font-size: 1rem;
            }
        }
        .reference-item.active {
            background-color: $--fg-color-accent-blue;
        }

        .visible-reference-indicator {
            position: absolute;
            right: 0.5rem;
            font-weight: bold;
            margin-top: 0.15rem;
        }

        a:hover,
        a:focus,
        a:active {
            text-decoration: underline;
        }
    }
</style>
