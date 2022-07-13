<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={"#include <fillcan/commands/command_recording.hpp>"}
/>

<Highlight
    language={cppHighlight}
    code={`struct CommandRecording {
    Queue* pQueue;
    CommandPool* pCommandPool;
    std::vector<CommandBuffer*> pPrimaryCommandBuffers = {};
    std::vector<CommandBuffer*> pSecondaryCommandBuffers = {};
    std::vector<Semaphore*> pWaitSemaphores = {};
    VkPipelineStageFlags waitDstStageMask = 0;
    std::vector<Semaphore*> pSignalSemaphores = {};
    std::unique_ptr<Fence> upFenceWorkCompleted = nullptr;
};`}
/>

The <code>Command Recording</code> structure is used by the <Reference
    sectionID={SectionID.QUEUE}>Queue</Reference
> to keep track of the information needed for recording commands and can be supplemented
with <Reference sectionID={SectionID.SEMAPHORE}>Semaphores</Reference> and a <Reference
    sectionID={SectionID.FENCE}>Fence</Reference
> for synchronization purposes.<br />
<MethodDescription>
    <span slot="params">
        <li>
            <code>pQueue</code><br />
            The <Reference sectionID={SectionID.QUEUE}>Queue</Reference> that owns
            this recording.
        </li>
        <li>
            <code>pCommandPool</code><br />
            The <Reference sectionID={SectionID.COMMAND_POOL}
                >Command Pool</Reference
            > the <Reference sectionID={SectionID.COMMAND_BUFFER}
                >Command Buffers</Reference
            > were allocated from.
        </li>
        <li>
            <code>pPrimaryCommandBuffers</code><br />
            The allocated primary <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > that can be recorded to.
        </li>
        <li>
            <code>pSecondaryCommandBuffers</code><br />
            The allocated secondary <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > that can be recorded to.
        </li>
        <li>
            <code>pWaitSemaphores</code><br />
            A list of pointers to <Reference sectionID={SectionID.SEMAPHORE}
                >Semaphores</Reference
            > to wait for before executing the <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            >.
        </li>
        <li>
            <code>waitDstStageMask</code><br />
            An array of pipeline stages, which is a bitmask of <Anchor
                href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPipelineStageFlagBits.html"
                target="_blank">VkPipelineStageFlagBits</Anchor
            >, at which each corresponding semaphore wait will occur.<br />
            So the semaphore at index <code>0</code> will wait at the pipeline
            stage at index
            <code>0</code>, the semaphore at index <code>1</code> will wait at
            the pipeline stage at index
            <code>1</code>, etc.
        </li>
        <li>
            <code>pSignalSemaphores</code><br />
            A list of pointers to <Reference sectionID={SectionID.SEMAPHORE}
                >Semaphores</Reference
            > that are signaled when the <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > have finished execution.
        </li>
        <li>
            <code>upFenceWorkCompleted</code><br />
            A <Anchor
                href="https://en.cppreference.com/w/cpp/memory/unique_ptr"
                target="_blank">unique pointer</Anchor
            > to a <Reference sectionID={SectionID.FENCE}>Fence</Reference> that
            will be signaled once the <Reference
                sectionID={SectionID.COMMAND_BUFFER}>Command Buffers</Reference
            > have finished execution.<br />
            To initialize this Fence, call <Reference
                sectionID={SectionID.COMMAND_RECORDING_createFence}
                >createFence</Reference
            >.
        </li>
    </span>
</MethodDescription>
