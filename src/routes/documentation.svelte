<script lang="ts">
    import { fly } from "svelte/transition";
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";

    import Highlight from "svelte-highlight";
    import cppHighlight from "svelte-highlight/languages/cpp";
    import cmakeHighlight from "svelte-highlight/languages/cmake";
    import jsonHighlight from "svelte-highlight/languages/json";
    import nord from "svelte-highlight/styles/nord";
    import {
        SectionID,
        type Section as SectionObject,
    } from "$objects/Documentation/Section";
    import GettingStarted from "$components/Documentation/Sections/Getting_Started/GettingStarted.svelte";
    import Section from "$components/Documentation/Section.svelte";
    import CMake from "$components/Documentation/Sections/Getting_Started/CMake.svelte";
    import Fillcan from "$components/Documentation/Sections/Fillcan/Fillcan.svelte";
    import FillcanConstructor from "$components/Documentation/Sections/Fillcan/FillcanConstructor.svelte";
    import GetSupportedPhysicalDevices from "$components/Documentation/Sections/Fillcan/getSupportedPhysicalDevices.svelte";
    import SelectDevice from "$components/Documentation/Sections/Fillcan/selectDevice.svelte";
    import GetCurrentDevice from "$components/Documentation/Sections/Fillcan/getCurrentDevice.svelte";
    import GetWindow from "$components/Documentation/Sections/Fillcan/getWindow.svelte";
    import CreateShaderModule from "$components/Documentation/Sections/Fillcan/createShaderModule.svelte";
    import HamburgerMenuIcon from "$components/NavBar/HamburgerMenuIcon.svelte";
    import BeginSingleTimeRecording from "$components/Documentation/Sections/Fillcan/beginSingleTimeRecording.svelte";
    import EndSingleTimeRecording from "$components/Documentation/Sections/Fillcan/endSingleTimeRecording.svelte";

    const sections: Array<SectionObject> = [
        {
            id: SectionID.GETTING_STARTED,
            label: "Getting Started",
            heading: 2,
            content: GettingStarted,
            props: {},
            visible: false,
        },
        {
            id: SectionID.CMAKE,
            label: "CMake",
            heading: 3,
            content: CMake,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN,
            label: "Fillcan",
            heading: 2,
            content: Fillcan,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_Constructor,
            label: "Constructor",
            heading: 3,
            content: FillcanConstructor,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_getSupportedPhysicalDevices,
            label: "getSupportedPhysicalDevices",
            heading: 3,
            content: GetSupportedPhysicalDevices,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_selectDevice,
            label: "selectDevice",
            heading: 3,
            content: SelectDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_getCurrentDevice,
            label: "getCurrentDevice",
            heading: 3,
            content: GetCurrentDevice,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_getWindow,
            label: "getWindow",
            heading: 3,
            content: GetWindow,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_createShaderModule,
            label: "createShaderModule",
            heading: 3,
            content: CreateShaderModule,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_beginSingleTimeRecording,
            label: "beginSingleTimeRecording",
            heading: 3,
            content: BeginSingleTimeRecording,
            props: {},
            visible: false,
        },
        {
            id: SectionID.FILLCAN_endSingleTimeRecording,
            label: "endSingleTimeRecording",
            heading: 3,
            content: EndSingleTimeRecording,
            props: {},
            visible: false,
        },
    ];

    let currentVisibleSection: SectionObject | null = null;
    $: {
        sections;
        for (let i = 0; i < sections.length; i++) {
            if (sections[i].visible) {
                currentVisibleSection = sections[i];
                break;
            }
        }
    }

    let showHamburgerMenu = false;

    function handleHamburgerMenuClick(_e: MouseEvent) {
        showHamburgerMenu = !showHamburgerMenu;
    }
</script>

<svelte:head>
    {@html nord}
</svelte:head>

<div
    class="documentation {$stateStore.Screen.displayType === DisplayType.MOBILE
        ? 'mobile'
        : ''}"
    style="--sidebar-width: 20rem;"
>
    <div class="documentation-sidebar">
        <ul class="references-list">
            {#each sections as section, i}
                <li
                    class="reference-item h{section.heading} {currentVisibleSection !==
                        null && section.id === currentVisibleSection.id
                        ? 'active'
                        : ''}"
                >
                    <a href="{getState().URL.root}/documentation#{section.id}">
                        {section.label}
                    </a>
                </li>
            {/each}
        </ul>
    </div>
    {#if $stateStore.Screen.displayType === DisplayType.MOBILE}
        <div class="documentation-pop-in">
            <div class="documentation-pop-in-inner">
                <button
                    on:click={handleHamburgerMenuClick}
                    class="hamburger-menu-button {showHamburgerMenu
                        ? 'activated'
                        : ''}"
                >
                    <HamburgerMenuIcon />
                </button>
            </div>
        </div>
    {/if}
    {#if $stateStore.Screen.displayType === DisplayType.MOBILE && showHamburgerMenu}
        <div
            in:fly={{ y: -10, duration: 500, opacity: 0 }}
            out:fly={{ y: -20, duration: 250, opacity: 0 }}
            class="documentation-pop-in-content"
        >
            <ul class="references-list">
                {#each sections as section, i}
                    <li
                        class="reference-item h{section.heading} {currentVisibleSection !==
                            null && section.id === currentVisibleSection.id
                            ? 'active'
                            : ''}"
                    >
                        <a
                            href="{getState().URL
                                .root}/documentation#{section.id}"
                        >
                            {section.label}
                        </a>
                    </li>
                {/each}
            </ul>
        </div>
    {/if}
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
        {#each sections as section, i}
            <Section
                id={section.id}
                label={section.label}
                heading={section.heading}
                bind:visible={section.visible}
            >
                <svelte:component this={section.content} {...section.props} />
            </Section>
            <br />
            {#if i !== 0 && i < sections.length - 1 && sections.at(i + 1)?.heading === 2}
                <hr />
            {/if}
        {/each}
    </div>
</div>

<style lang="scss">
    .documentation {
        .documentation-container {
            font-family: $--font-family-default;
            color: $--fg-color-primary;
            margin-left: var(--sidebar-width);
            padding: 0 15vw 0 5vw;

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

        h1 {
            padding-top: 0;
        }

        h1 {
            font-size: 3rem;
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

    .documentation:not(.mobile) {
        .documentation-pop-in {
            display: none;
        }
        .documentation-pop-in-content {
            display: none;
        }
    }

    .documentation-sidebar,
    .documentation-pop-in-content {
        top: $--navbar-height;
        height: calc(100% - $--navbar-height);
        overflow: auto;
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
                background-color: black !important;
            }

            a:hover,
            a:focus,
            a:active {
                text-decoration: underline;
            }
        }
    }

    .documentation-pop-in {
        position: fixed;
        bottom: 0;
        width: 100%;
        height: 2.5rem;
        background-color: $--bg-color-secondary;

        .documentation-pop-in-inner {
            width: 100%;
            height: 100%;
            display: flex;
            vertical-align: middle;
            align-content: center;
            .hamburger-menu-button {
                margin-left: 0.5rem;
                width: 1.75rem;
                height: 100%;
                border: none;
                background: none;
                cursor: pointer;
                fill: $--input-fg-color-secondary;
                transition: all 0.25s;
            }
            .hamburger-menu-button:hover,
            .hamburger-menu-button:focus,
            .hamburger-menu-button:active {
                fill: $--input-fg-color-primary;
            }

            .hamburger-menu-button.activated {
                fill: $--input-fg-color-primary;
                width: 2rem;
            }
        }
    }

    .documentation-pop-in-content {
        position: fixed;
        top: $--navbar-height; // Height of the NavBar
        bottom: 2.5rem; // Height of the pop-in menu
        height: calc(100% - 2.5rem - $--navbar-height);
        width: 100%;
        background-color: $--bg-color-secondary;
        overflow: auto;
    }
</style>
