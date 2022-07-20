<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
    import glslHighlight from "svelte-highlight/languages/glsl";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/shader/descriptor_set_layout.hpp>"}
/>

The <code>Descriptor Set Layout</code> class takes a pointer to a <Reference
    sectionID={SectionID.LOGICAL_DEVICE}>Logical Device</Reference
> along a list of <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayoutBinding.html"
    target="_blank">Vulkan Descriptor Set Layout Bindings</Anchor
> and uses this information to construct a <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayout.html"
    target="_blank">Vulkan Descriptor Set Layout</Anchor
>.<br />

The shaders in the application consume and produce data in two ways. The first
is by interacting with fixed function hardware and the second is by directly
reading and writing resources. Shaders can access the contents of the buffer
memory directly from three types of sources:
<ul>
    <li>
        Uniform blocks provide quick access to constant (read-only) data stored
        in <Reference sectionID={SectionID.BUFFER}>buffer</Reference> objects. They
        are declared as if they were structures in a shader and are mapped to memory
        using a buffer resource bound to the descriptor set.
    </li>
    <li>
        Storage blocks provide read-write access to <Reference
            sectionID={SectionID.BUFFER}>buffer</Reference
        > objects. Declared in the same way as uniform blocks, data is arranged as
        if it were a structure, but can be written to. Shader storage blocks also
        support atomic operations.
    </li>
    <li>
        Texel buffers provide access to long, linear arrays of formatted Texel
        data. They are read-only and a texel buffer binding performs format
        conversion from the underlying data format to the floating-point
        representation that the shader expects when the buffer is read.
    </li>
</ul>
The type of resource used depends on how it is to be accessed. The maximum size of
a uniform block is often limited, while access to it is generally very fast. On the
other hand, the maximum size of a shader storage block is very large, but in some
implementations access to it can be slower, especially if writes are enabled. For
accessing large arrays of formatted data, a texel buffer is probably the best choice.<br
/><br />
To declare a uniform block in GLSL, the uniform keyword is used. A shader storage
block is declared in the same way, except that the uniform keyword is omitted and
the buffer keyword is used instead.
<Highlight
    language={glslHighlight}
    code={`#version 450 core

layout (set = 0, binding = 1) uniform UniformBlock
{
    float float_value;
    vec4 vec4_value;
} uniform_buffer;

layout (set = 0, binding = 2) buffer StorageBlock
{
    float float_value;
    vec4 vec4_value
} storage_buffer;
`}
/><br />
An interface block has the following definition. although it looks like a structure
definition, it is not:
<Highlight
    language={glslHighlight}
    code={`storage_qualifier block_name
{
    <define members here>
} instance_name;
`}
/>
The storage qualifier (<code>storage_qualifier</code>) defines what kind of
interface block is created. <code>storage_qualifier</code> can be the following:
<ul>
    <li>
        <code>uniform</code>. A uniform is a global shader variable declared
        with the storage qualifier uniform. They are so named because they do
        not change from one shader call to the next within a given rendering
        call, so their value is uniform among all calls
    </li>
    <li>
        <code>in</code>. Global variables declared with the
        <code>in</code>-qualifier are input variables of the shader stage. These
        variables are given values by the previous stage. These variables are
        not constant (in the sense of <code>const</code>), but cannot be changed
        by user code.
    </li>
    <li>
        <code>out</code>. Global variables declared with the
        <code>out</code>-qualifier are shader stage output variables. These
        values are passed to the next stage of the pipeline. The shader must set
        all output variables at some point during execution; there are only two
        exceptions to this:
        <ol>
            <li>
                The shader is a Fragment Shader that executes the <code
                    >discard</code
                >
                statement.
            </li>
            <li>
                The output variables that are not written are not read by the
                next shader stage or pipeline process. This includes writes to
                fragment shader outputs that are masked.
            </li>
        </ol>
    </li>
    <li>
        <code>buffer</code>. The storage for the contents of the block comes
        from a buffer object, similar to Uniform Buffer Objects and Uniform
        Blocks. Unlike UBOs, storage blocks can be written to.
    </li>
</ul>
<code>block_name</code> is the real name for the interface block. This is the
name used to refer to it. A shader cannot have multiple blocks that have the
same block_name and the same storage_qualifier. instance_name is a GLSL name for
one or more instances of the block named block_name. It's optional; if it is
present, all GLSL variables defined in the block must be qualified with the
instance name when referenced in the GLSL code.
<Highlight
    language={glslHighlight}
    code={`// With interface name
uniform MatrixBlock
{
    mat4 projection;
    mat4 modelView;
} matrices;
// To access projection, use matrices.projection

uniform vec3 modelView; // Allowed
`}
/>
<Highlight
    language={glslHighlight}
    code={`// Without interface name
uniform MatrixBlock
{
    mat4 projection;
    mat4 modelView;
};
// To access projection, use projection

uniform vec3 modelView; // Redefining variable. Compile error.
`}
/><br />
A texel buffer is a special type of buffer binding used in a shader that can perform
format conversion when the data is read. Texel buffers are read-only and are declared
in GLSL using a <code>samplerBuffer</code>-type variable. Sampler buffers can
return floating-point data or integers (signed or unsigned) to the shader.

<Highlight
    language={glslHighlight}
    code={`layout (set = 0, binding = 3) uniform samplerBuffer floatTexelBuffer;
layout (set = 0, binding = 4) uniform isamplerBuffer signedTexelBuffer;
layout (set = 0, binding = 5) uniform usamplerBuffer unsignedTexelBuffer;
`}
/>
To fetch a texel from a texelbuffer in GLSL, the <Anchor
    href="https://registry.khronos.org/OpenGL-Refpages/gl4/html/texelFetch.xhtml"
    target="_blank">texelFetch</Anchor
> function is used with the sampler variable (<code>floatTexelBuffer</code>,
<code>signedTexelBuffer</code>
or <code>unsignedTexelBuffer</code>) to read individual texels. A
<code>samplerBuffer</code>
(or the corresponding <code>isamplerBuffer</code> and
<code>usamplerBuffer</code>) can be seen as a 1D texture that only supports
point sampling (because only one texel can be queried). However, the maximum
size of a texel buffer associated with one of these variables is generally much
larger than the maximum size of a 1D structure. For example, the minimum
required upper bound for a texel buffer in Vulkan is 65,535 elements, while the
minimum required size for a 1D texture is only 4,096 texels. In some cases
implementations will support texel buffers that are gigabytes in size.<br /><br
/>
A push constant is a uniform variable in a shader that can be used just like a member
of a unified block, but instead of being backed up by memory, it's owned and updated
by Vulkan itself. As a result, new values for these constants can be pushed directly
into the pipeline from the command buffer, hence the term. Push constants are logically
considered part of the pipeline's resources and therefore are declared along with
the other resources in the <Reference sectionID={SectionID.PIPELINE_LAYOUT}
    >pipeline layout</Reference
> used to create pipeline objects.<br />
To declare a push constant in GLSL, the <code>push_constant</code> layout
qualifier can be used.
<Highlight
    language={glslHighlight}
    code={`layout (push_constant) uniform block_name 
{
    <define members here>
} interface_name;

// Example
layout (push_constant) uniform PushConstant 
{
    int var1;
    vec3 var2;
    mat4 var3;
} push_constant;
`}
/>
Push constants become part of the <Reference
    sectionID={SectionID.PIPELINE_LAYOUT}>pipeline layout</Reference
> that will use them. When push constants are pipelined, they can consume some of
the resources Vulkan would otherwise use to track pipeline or descriptor bindings.
Therefore, push constants should be considered relatively precious resources.
