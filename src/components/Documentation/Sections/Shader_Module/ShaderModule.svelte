<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/shader/shader_module.hpp>"}
/>

The <code>Shader Module</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along with a list of characters representing the GLSL code and a list of <Anchor
    href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
    target="_blank">unique pointers</Anchor
> to the <Reference sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
    >descriptor set layouts</Reference
> describing the <Reference sectionID={SectionID.DESCRIPTOR_SET}
    >descriptor sets</Reference
> that expose resources to the shader, and a <Anchor
    href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
    target="_blank">unique pointer</Anchor
> to a <Reference sectionID={SectionID.DESCRIPTOR_POOL}
    >descriptor pool</Reference
> from which the <Reference sectionID={SectionID.DESCRIPTOR_SET}
    >descriptor sets</Reference
> will be allocated.<br />
Note that the ownership of both the <Reference
    sectionID={SectionID.DESCRIPTOR_SET_LAYOUT}
    >descriptor set layouts</Reference
> and the <Reference sectionID={SectionID.DESCRIPTOR_POOL}
    >descriptor pool</Reference
> needs to be transferred using <Anchor
    href="https://en.cppreference.com/w/cpp/utility/move"
    target="_blank"><code>std::move</code></Anchor
>.<br />
Shaders are small programs that run directly on the device (like a GPU). Shaders
are the fundamental building blocks of the work to be done on the device.<br />
Vulkan shaders are represented by <Anchor
    href="https://www.khronos.org/spir/"
    target="_blank">SPIR-V</Anchor
> (Standard Portable Intermediate Representation), a binary intermediate representation
of program code. <Anchor href="https://www.khronos.org/spir/" target="_blank"
    >SPIR-V</Anchor
> can be generated outside the application using a compiler, directly in the application
or by passing a high-level language to a library at run-time.<br />
The original shaders are written in <Anchor
    href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
    target="_blank">GLSL</Anchor
> using the Vulkan profile. This is a modified and extended version of the same shading
language used with OpenGL. Most examples therefore discuss Vulkan features in terms
of their representation in <Anchor
    href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
    target="_blank">GLSL</Anchor
>. Note that Vulkan itself knows nothing about <Anchor
    href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
    target="_blank">GLSL</Anchor
> and only cares about the compiled <Anchor
    href="https://www.khronos.org/spir/"
    target="_blank">SPIR-V</Anchor
> representation.<br /><br />

The <code>Shader Module</code> class compiles <Anchor
    href="https://www.khronos.org/opengl/wiki/Core_Language_(GLSL)"
    target="_blank">GLSL</Anchor
> shaders at run-time using <Anchor
    href="https://github.com/google/shaderc"
    target="_blank">Shaderc</Anchor
>.
