<script lang="ts">
    import Section from "$components/Documentation/Section.svelte";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";

    class Reference {
        public id: string;
        public label: string;
        public visible: boolean;
    }

    let references: Array<Reference> = [
        {
            id: "setup",
            label: "Setup",
            visible: false,
        },
        {
            id: "hi",
            label: "Hi",
            visible: false,
        },
    ];

    let currenReference: Reference = references[0];

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
    <div class="documentation-sidebar">Sidebar</div>
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
        <br />
        <hr />
        <Section
            {topOffsetInPx}
            bind:visible={references[getIndexOfReferenceById("setup")].visible}
        >
            <h2 id="setup">{getReferenceById("setup").label}</h2>
        </Section>
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
            font-family: $--font-family-default;
            color: $--fg-color-primary;
            position: fixed;
            overflow-y: scroll;

            background-color: $--bg-color-secondary;
            width: var(--sidebar-width);
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
</style>
