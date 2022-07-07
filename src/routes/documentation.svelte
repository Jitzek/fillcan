<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Section from "$components/Documentation/Section.svelte";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";

    import Highlight from "svelte-highlight";
    import cppHighlight from "svelte-highlight/languages/cpp";
    import cmakeHighlight from "svelte-highlight/languages/cmake";
    import nord from "svelte-highlight/styles/nord";

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
            id: "cmake",
            category: { id: "Setup", label: "Setup" },
            label: "CMake",
            visible: false,
        },
    ];

    let currenReference: Reference = references[0];
    let prevCategory: Category = { id: "undefined", label: "" };

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
            {#each references as reference, i}
                {#if i == 0 || references.at(i - 1).category.id !== reference.category.id}
                    {#if references.at(i - 1).id !== "undefined"}
                        <br />
                    {/if}
                    <li class="reference-header">
                        <a
                            href="{getState().URL.root}/documentation#{reference
                                .category.id}"
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
        <h3 id="cmake">{getReferenceById("cmake").label}</h3>

        <Section
            {topOffsetInPx}
            bind:visible={references[getIndexOfReferenceById("cmake")].visible}
        >
            Fillcan makes use of <Anchor
                href="https://cmake.org/"
                target="_blank">CMake</Anchor
            > and as such has a CMakeLists.txt file.<br /><br />
            To add Fillcan to your project as a library you first have to add it's
            directory to the compiler's search list for include files:
            <Highlight
                language={cmakeHighlight}
                code={`set(Fillcan_DIRECTORY "\${CMAKE_SOURCE_DIR}/lib/fillcan")\ntarget_include_directories(\${PROJECT_NAME} PUBLIC \${Fillcan_DIRECTORY} \${PROJECT_BINARY_DIR})`}
            /><br />
            Next you need to add Fillcan as a subdirectory to the project. This indicates
            to the compiler where the CMakeLists.txt and code files of Fillcan are
            located:
            <Highlight
                language={cmakeHighlight}
                code={`add_subdirectory(\${Fillcan_DIRECTORY})`}
            /><br />
            Finally you can link the Fillcan library to the project:
            <Highlight
                language={cmakeHighlight}
                code={`target_link_libraries(\${PROJECT_NAME} Fillcan)`}
            /><br />
            Within Fillcan's CMakeLists.txt several libraries are added. These libraries
            are as follows:
            <h4 id="cmake-vulkan">1. Vulkan</h4>
            The Vulkan Library will be looked for on the system. And if it can no
            be found a bundled version will be used instead.
            <h4 id="cmake-glfw">2. GLFW</h4>
            <Anchor href="https://www.glfw.org/" target="_blank">GLFW</Anchor> is
            used for creating windows, contexts and surfaces and receiving input
            and events.
            <h4 id="cmake-glm">3. GLM</h4>
            <Anchor href="https://github.com/g-truc/glm" target="_blank"
                >GLM</Anchor
            > is a header only C++ mathematics library for graphics software based
            on the OpenGL Shading Language (GLSL) specifications.
            <h4 id="cmake-shaderc">4. Shaderc</h4>
            <Anchor href="https://github.com/google/shaderc" target="_blank"
                >Shaderc</Anchor
            > is a collection of tools for shader compilation. It is used within
            Fillcan to validate GLSL shader-code and to compile it to SPIR-V.
        </Section>
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

        h1,
        h2,
        h3 {
            padding-top: 0;
        }

        h1 {
            font-size: 3rem;
        }
        h2,
        h3,
        h4 {
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
        p {
            margin-top: 0;
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
