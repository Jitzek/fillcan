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
    code={"#include <fillcan/computing/compute_pipeline.hpp>"}
/>

The <code>Compute Pipeline</code> class extends the
<code><Reference sectionID={SectionID.PIPELINE}>Pipeline</Reference></code>
class.<br /><br />
The compute shader provides direct access to the computing capabilities of the Vulkan
device. The device can be thought of as a collection of broad vector processing units
operating on related data. A compute shader is written as if it were a serial, single
run track. However, many of these run tracks can run simultaneously. This is how
most Vulkan devices are built. Each track of execution is called an invocation.<br
/>
When a compute shader is running, many calls are made at once. The invocations are
grouped into fixed size local workgroups, then one or more of these groups are run
together in what is sometimes known as a global workgroup. Logically, both the local
and global workgroups are three-dimensional. However, if the size of one of the three
dimensions is set to one, the dimensionality of the group is reduced.<br /><br
/>
Once a pipeline is tied, it can be used to perform work. Compute shaders that run
as part of a compute pipeline run in groups called local workgroups. The size of
the local workgroup is set in the compute shader. In GLSL this is done using a layout
qualifier:
<Highlight
    language={cppHighlight}
    code={`#version 450 core
layout (local_size_x = 2, local_size_y, local_size = 4) in;

void main(void)
{
    // Do something
}`}
/>
The maximum size of a local workgroup for a compute shader is generally quite small
and only needs to be a minimum of 128 calls in the x and y dimensions and 64 calls
in the z dimension. Furthermore, the total "volume" of the workgroup (the product
of the limit in x, y, and z directions) is subject to a further limit, which may
only be a minimum of 128 x 128 x 64 invocations. While many implementations support
higher limits, the limits should always be queried if the required minimums are to
be exceeded.<br />
The maximum size of a workgroup and the maximum total calls in the workgroup can
be determined from the <code>maxComputeWorkGroupSize</code> field and
<code>maxComputeWorkGroupInvocations</code>
field, respectively, of the <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceLimits.html"
    target="_blank">VkPhysicalDeviceLimits</Anchor
>-structure within the <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceProperties.html"
    target="_blank">VkPhysicalDeviceProperties</Anchor
>-structure returned by a call to <Reference
    sectionID={SectionID.PHYSICAL_DEVICE_getProperties}>getProperties</Reference
>.<br /><br />
Because there are limitations to the use of some local workgroups, local workgroups
are started in larger groups, also called the global workgroup or "dispatch". Kicking
off work in a compute shader is therefore called dispatch work or a dispatch (or
"dispatch"). The local workgroup is logically a 3D construct, or a volume of invocations,
although as many as one or two of the dimensions may have a single invocation in
size, flattening the workgroup in that direction. Likewise, these local workgroups
are sent together in three dimensions, even if one or more of those dimensions is
a single workgroup deep (so 32 x 32 x 1 and 64 x 1 x 1 workgroups is valid).<br
/>
The command to dispatch a global workgroup using a compute pipeline is <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDispatch.html"
    target="_blank">vkCmdDispatch</Anchor
>.<br /><br />

Example:
<Highlight
    language={glslHighlight}
    code={`#version 450 core

layout (local_size_x=256, local_size_y=1, local_size_z=1) in;

layout (set=0, binding=0) uniform Config
{
    int transform;
    int integerCount;
} configData;
        
layout (set=0, binding=1) readonly buffer InputBuffer
{
    int integers[4096];
} inputData;
        
layout (set=0, binding=2) buffer OutputBuffer
{
    int integers[4096];
} outputData;
        
void main(void)
{
    // Grab global ID
    uint globalID = gl_GlobalInvocationID.x;
        
    // Don't access past the buffer size
    if (globalID < configData.integerCount)
    {
        // Perform some calculations
        outputData.integers[globalID] = inputData.integers[globalID] * configData.transform;
    }
}`}
/>

<Highlight
    language={cppHighlight}
    code={`// Create recording to gain access to a primary commandbuffer
fillcan::CommandRecording* pComputeCommandRecording = fillcan.getCurrentDevice()->getComputeQueue()->createRecording(1, 0);
fillcan::CommandBuffer* pComputePrimaryCommandBuffer = pComputeCommandRecording->pPrimaryCommandBuffers.at(0);

// Begin compute recording commands
pComputePrimaryCommandBuffer->begin();

// Bind a command buffer to the compute pipeline
computePipeline.bindToCommandBuffer(pComputePrimaryCommandBuffer);

// Bind the descriptor sets to the bound command buffer
computePipeline.bindDescriptorSets();

// Define the amount of local workgroups for the x-dimension
// (the amount of computations to execute divided by the size of the local workgroup)
int groupCount = ((4096) / 256) + 1;

// Dispatch all the work
vkCmdDispatch(pComputePrimaryCommandBuffer->getCommandBufferHandle(), groupCount, 1, 1);

// End the recording
pComputePrimaryCommandBuffer->end();`}
/><br />
In addition to being able to specify the number of workgroups in the dispatch using
parameters to <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDispatch.html"
    target="_blank">vkCmdDispatch</Anchor
>, it is possible to perform an indirect dispatch, where the size of the
dispatch in workgroups comes from a buffer object. This allows the calculation
of send sizes after a command buffer is built by performing an indirect dispatch
using a buffer and then overwriting the contents of the buffer using the host.
The contents of the buffer can even be updated using the device itself to
provide a limited means for the device to feed itself work. This can be done
with <Anchor
    href="https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDispatchIndirect.html"
    target="_blank">vkCmdDispatchIndirect</Anchor
>.