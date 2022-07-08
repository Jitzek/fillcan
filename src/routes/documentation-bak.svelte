<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Section from "$components/Documentation/Section.svelte";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";

    import Highlight from "svelte-highlight";
    import cppHighlight from "svelte-highlight/languages/cpp";
    import cmakeHighlight from "svelte-highlight/languages/cmake";
    import jsonHighlight from "svelte-highlight/languages/json";
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
            category: { id: "Getting-Started", label: "Getting Started" },
            label: "CMake",
            visible: false,
        },
        {
            id: "vscode",
            category: { id: "Getting-Started", label: "Getting Started" },
            label: "Visual Studio Code",
            visible: false,
        },
        {
            id: "fillcan-constructor",
            category: { id: "Fillcan", label: "Fillcan" },
            label: "Constructor",
            visible: false,
        },
        {
            id: "fillcan-getSupportedPhysicalDevices",
            category: { id: "Fillcan", label: "Fillcan" },
            label: "getSupportedPhysicalDevices",
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
        <h2 id="Getting-Started">Getting Started</h2>
        <br />
        <hr />
        <Section
            {topOffsetInPx}
            bind:visible={references[getIndexOfReferenceById("cmake")].visible}
        >
            <h3 id="cmake">{getReferenceById("cmake").label}</h3>
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
            The Vulkan Library will be looked for on the system. And if it can not
            be found a bundled version will be used instead.
            <h4 id="cmake-glfw">2. GLFW</h4>
            <Anchor href="https://www.glfw.org/" target="_blank">GLFW</Anchor> is
            used for creating windows, contexts and surfaces and receiving input
            and window events.
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
        <br />
        <hr />
        <Section
            {topOffsetInPx}
            bind:visible={references[getIndexOfReferenceById("vscode")].visible}
        >
            <h3 id="vscode">{getReferenceById("vscode").label}</h3>
            Fillcan has been developed using <Anchor
                href="https://code.visualstudio.com/"
                target="_blank">Visual Studio Code</Anchor
            > so I'd like to share some configuration I've personally found helpful.
            <h4 id="vscode-extensions">Extensions</h4>
            These are the extensions I've used while developing:
            <ul>
                <li>
                    <Anchor
                        href="https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd"
                        target="_blank">clangd</Anchor
                    ><br />
                    For C++ language support (code completion, compile errors and
                    warnings, code browsing, hover information, formatting and refactoring).
                </li>
                <li>
                    <Anchor
                        href="https://marketplace.visualstudio.com/items?itemName=xaver.clang-format"
                        target="_blank"
                    >
                        Clang-Format
                    </Anchor><br />
                    For formatting C++. <br />
                    To configure the formatting you can include
                    a file named
                    <code>.clang-format</code> within the project's root. I have
                    configured clang-format as follows:
                    <Highlight
                        code={`BasedOnStyle: LLVM\nIndentWidth: 4\nLanguage: Cpp\nDerivePointerAlignment: false\nPointerAlignment: Left\nColumnLimit: 150\nNamespaceIndentation: All`}
                    />
                </li>
                <li>
                    <Anchor
                        href="https://marketplace.visualstudio.com/items?itemName=twxs.cmake"
                        target="_blank"
                    >
                        CMake
                    </Anchor><br />
                    For CMake language support (colorization and code completion)
                </li>
                <li>
                    <Anchor
                        href="https://marketplace.visualstudio.com/items?itemName=cheshirekow.cmake-format"
                        target="_blank"
                    >
                        cmake-format
                    </Anchor><br />
                    For formatting CMakeLists.txt files.
                </li>
            </ul>
            <h4 id="vscode-tasks">Tasks</h4>
            I have prepared several <Anchor
                href="https://code.visualstudio.com/docs/editor/tasks"
                target="_blank">Tasks</Anchor
            > to configure, build and run the application in Debug or Release mode.<br
            />
            Within Visual Studio Code tasks can be configured by editing or creating
            the <code>tasks.json</code> file, located within the
            <code>.vscode</code>
            folder of the project's root.<br />
            <Anchor
                href="https://github.com/Jitzek/fillcan/blob/main/.vscode/tasks.json"
                target="_blank"
            >
                My <code>.vscode/tasks.json</code>
            </Anchor><br />
            <Anchor
                href="https://github.com/Jitzek/fillcan/blob/main/scripts/"
                target="_blank"
            >
                Scripts used for Windows
            </Anchor><br />
            <h4 id="vscode-run-and-debug">Run and Debug</h4>
            Within Visual Studio Code the application can be <Anchor
                href="https://code.visualstudio.com/docs/cpp/launch-json-reference"
                target="_blank">run and debugged</Anchor
            > by editing or creating the <code>launch.json</code> file, located
            within the <code>.vscode</code> folder of the project's root.<br />
            <Anchor
                href="https://github.com/Jitzek/fillcan/blob/main/.vscode/launch.json"
                target="_blank"
            >
                My <code>.vscode/launch.json</code>
            </Anchor><br />
        </Section><br />
        <br />
        <hr />
        <h2 id="Fillcan">Fillcan</h2>
        <Highlight
            language={cppHighlight}
            code={"#include <fillcan/fillcan.hpp>"}
        />
        The <code>Fillcan</code> class is the API through which the application
        can talk with Vulkan.

        <br />
        <hr />
        <Section
            {topOffsetInPx}
            bind:visible={references[
                getIndexOfReferenceById("fillcan-constructor")
            ].visible}
        >
            <h3 id={getReferenceById("fillcan-constructor").id}>
                {getReferenceById("fillcan-constructor").label}
            </h3>
            <Highlight
                language={cppHighlight}
                code={`Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                    VkPhysicalDeviceFeatures requiredDeviceFeatures = {}, std::vector<const char*> requiredDeviceExtensions = {});`}
            />
            <ul class="method-description">
                <li>
                    <code>pApplicationName</code><br />
                    The name of the application.
                </li>
                <li>
                    <code>applicationVersion</code><br />
                    The version of the application.
                </li>
                <li>
                    <code>windowWidth</code><br />
                    The initial width the window.
                </li>
                <li>
                    <code>windowHeight</code><br />
                    The initial height the window.
                </li>
                <li>
                    <code>requiredDeviceFeatures</code><br />
                    The features a <Anchor
                        href="{getState().URL
                            .root}/documentation/#PhysicalDevice"
                        >Physical Device</Anchor
                    > should have for the purposes of the application.<br />
                    This should be a <Anchor
                        href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html"
                        target="_blank">VkPhysicalDeviceFeatures</Anchor
                    >-structure where each required feature should be set to
                    true.
                </li>
                <li>
                    <code>requiredDeviceExtensions</code><br />
                    The extensions a <Anchor
                        href="{getState().URL
                            .root}/documentation/#PhysicalDevice"
                        >Physical Device</Anchor
                    > should enable for the purposes of the application.<br />
                    This should be a list of strings containing the names of the
                    extensions to enable. The available extensions can be retrieved
                    using <Anchor
                        href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html"
                        target="_blank"
                        >vkEnumerateInstanceExtensionProperties()</Anchor
                    >. To be able to use a <Anchor
                        href="{getState().URL.root}/documentation/#Swapchain"
                        >Swapchain</Anchor
                    > this list should contain
                    <code>VK_KHR_SWAPCHAIN_EXTENSION_NAME</code> (<Anchor
                        href="{getState().URL
                            .root}/documentation/#FillcanGraphics"
                        >Fillcan Graphics</Anchor
                    > contains this by default).<br />
                </li>
            </ul>
            As of version {getState().Fillcan.version} the window can not be detached
            from the application because the <Anchor
                href="{getState().URL.root}/documentation/#Instance"
                >Instance</Anchor
            > might require certain extensions requested by the window and the <Anchor
                href="{getState().URL.root}/documentation/#PhysicalDevice"
                >Physical Device</Anchor
            > requires a window to validate support for certain features.<br
            /><br />
            Example:
            <Highlight
                language={cppHighlight}
                code={`VkPhysicalDeviceFeatures requiredDeviceFeatures = {};\nrequiredDeviceFeatures.samplerAnisotropy = true;\nauto fillcan = fillcan::Fillcan(\"Example Application\", 1.0, 800, 600, requiredDeviceFeatures);`}
            />
        </Section>
        <Section
            {topOffsetInPx}
            bind:visible={references[
                getIndexOfReferenceById("fillcan-getSupportedPhysicalDevices")
            ].visible}
        >
            <h3 id={getReferenceById("fillcan-getSupportedPhysicalDevices").id}>
                {getReferenceById("fillcan-getSupportedPhysicalDevices").label}
            </h3>
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

            .method-description {
                li {
                    font-size: 1rem;
                    code {
                        background-color: $--bg-color-secondary;
                    }
                    margin-bottom: 0.5rem;
                }
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
