<script lang="ts">
    import Section from "$components/Documentation/Section.svelte";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";

    class Category {
        id: string;
        label: string;
    }

    class Reference {
        public id: string;
        public category: Category;
        public label: string;
        public visible: boolean;
    }

    let references: Array<Reference> = [
        {
            id: "vulkansdk",
            category: {id: "Setup", label: "Setup"},
            label: "Vulkan SDK",
            visible: false,
        },
        {
            id: "cmake",
            category: {id: "Setup", label: "Setup"},
            label: "CMake",
            visible: false,
        },
        {
            id: "hi",
            category: {id: "Instance", label: "Instance"},
            label: "Hi",
            visible: false,
        },
    ];

    let currenReference: Reference = references[0];
    let prevCategory: Category = {id: "undefined", label: ""};

    let topOffsetInPx = 100;

    function getReferenceById(id: string): Reference {
        return references.find((reference) => reference.id === id);
    }

    function getIndexOfReferenceById(id: string) {
        for (let i = 0; i < references.length; i++) {
            if (references.at(i).id === id) return i;
        }
        return -1;
    }

    $: {
        references;
        for (let i = references.length - 1; i >= 0; i--) {
            if (references[i].visible) {
                currenReference = references[i];
                break;
            }
        }
    }
</script>

<div
    class="documentation {$stateStore.Screen.displayType === DisplayType.MOBILE
        ? 'mobile'
        : ''}"
    style="--sidebar-width: 20rem;"
>
    <div class="documentation-sidebar">
        <ul class="references-list">
            {#each references as reference, i}
                {#if i == 0 || references.at(i - 1).category.id !== reference.category.id}
                    {#if references.at(i - 1).id !== "undefined"}
                        <br />
                    {/if}
                    <li class="reference-header">
                        <a
                            href="{getState().URL
                                .root}/documentation#{reference.category.id}"
                        >
                            {reference.category.label}
                        </a>
                    </li>
                {/if}
                <li class="reference-item">
                    <a
                        href="{getState().URL
                            .root}/documentation#{reference.id}"
                    >
                        {reference.label}
                    </a>
                </li>
            {/each}
        </ul>
    </div>
    <div
        class="documentation-container  {$stateStore.Screen.displayType ===
        DisplayType.MOBILE
            ? 'mobile'
            : 'desktop'}"
    >
        <h1>Documentation</h1>
        <p>
            This page contains the documentation for Fillcan (v{getState()
                .Fillcan.version}). It's intended for people who are familiar
            with C++ and Vulkan. <br />
            Some concepts within C++ and Vulkan will be elaborated upon if I think
            they are interesting.
        </p>
        <br /><br />
        <hr />
        <h2 id="Setup">Setup</h2>
        <Section
            {topOffsetInPx}
            bind:visible={references[getIndexOfReferenceById("vulkansdk")].visible}
        >
            <h3 id="vulkansdk">{getReferenceById("vulkansdk").label}</h3>
        </Section>
        <Section
            {topOffsetInPx}
            bind:visible={references[getIndexOfReferenceById("cmake")].visible}
        >
            <h3 id="cmake">{getReferenceById("cmake").label}</h3>
        </Section>
        <br /><br />
        <hr />
        <h2 id="Instance">Instance</h2>

    </div>
</div>

<style lang="scss">
    .documentation {
        .documentation-container {
            font-family: $--font-family-default;
            color: $--fg-color-primary;
            margin-left: var(--sidebar-width);
            padding: 0 5vw 0 5vw;

            hr {
                color: $--fg-color-tertiary;
            }
        }

        .documentation-sidebar {
            top: 5rem; // 5rem is the height of the NavBar
            font-family: $--font-family-default;
            color: $--fg-color-primary;
            position: fixed;
            overflow-y: scroll;

            background-color: $--bg-color-secondary;
            width: var(--sidebar-width);
        }

        h1, h2, h3 {
            padding-top: 0;
        }

        h1 {
            font-size: 3rem;
        }
        h2, h3 {
            margin-top: 0;
        }
        h2 {
            font-size: 2.25rem;
        }
        h3 {
            font-size: 1.5rem;
        }
    }

    .documentation.mobile {
        .documentation-container {
            margin-left: 0;
        }
        .documentation-sidebar {
            display: none;
        }
    }

    .documentation-sidebar {
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
            .reference-header {
                a {
                    color: $--input-fg-color-primary;
                    text-transform: uppercase;
                    font-size: 1.2rem;
                }
            }
            .reference-item {
                a {
                    color: $--input-fg-color-secondary;
                    padding-left: 1rem;
                    font-size: 1.1rem;
                }
            }

            a:hover,
            a:focus,
            a:active {
                text-decoration: underline;
            }
        }
    }
</style>
