<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import { Highlight } from "svelte-highlight";

    import cmakeHighlight from "svelte-highlight/languages/cmake";
</script>

Fillcan makes use of <Anchor href="https://cmake.org/" target="_blank"
    >CMake</Anchor
> and as such has a CMakeLists.txt file.<br /><br />
To add Fillcan to your project as a library you first have to add it's directory
to the compiler's search list for include files:
<Highlight
    language={cmakeHighlight}
    code={`set(Fillcan_DIRECTORY "\${CMAKE_SOURCE_DIR}/lib/fillcan")\ntarget_include_directories(\${PROJECT_NAME} PUBLIC \${Fillcan_DIRECTORY} \${PROJECT_BINARY_DIR})`}
/><br />
Next you need to add Fillcan as a subdirectory to the project. This indicates to
the compiler where the CMakeLists.txt and code files of Fillcan are located:
<Highlight
    language={cmakeHighlight}
    code={`add_subdirectory(\${Fillcan_DIRECTORY})`}
/><br />
Finally you can link the Fillcan library to the project:
<Highlight
    language={cmakeHighlight}
    code={`target_link_libraries(\${PROJECT_NAME} Fillcan)`}
/><br />
Within Fillcan's CMakeLists.txt several libraries are added. These libraries are
as follows:
<h4 id="cmake-vulkan">1. Vulkan</h4>
The Vulkan Library will be looked for on the system. And if it can not be found a
bundled version will be used instead.
<h4 id="cmake-glfw">2. GLFW</h4>
<Anchor href="https://www.glfw.org/" target="_blank">GLFW</Anchor> is used for creating
windows, contexts and surfaces and receiving input and window events.
<h4 id="cmake-glm">3. GLM</h4>
<Anchor href="https://github.com/g-truc/glm" target="_blank">GLM</Anchor> is a header
only C++ mathematics library for graphics software based on the OpenGL Shading Language
(GLSL) specifications.
<h4 id="cmake-shaderc">4. Shaderc</h4>
<Anchor href="https://github.com/google/shaderc" target="_blank">Shaderc</Anchor
> is a collection of tools for shader compilation. It is used within Fillcan to validate
GLSL shader-code and to compile it to SPIR-V.

<style lang="scss">
    h4 {
        margin-bottom: 0;
    }
</style>
