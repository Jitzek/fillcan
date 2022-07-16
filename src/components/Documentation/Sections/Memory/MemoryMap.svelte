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
    code={`void** map(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE);`}
/>
<MethodDescription>
    <span slot="details"> Allocate memory to get a host usable pointer.</span>
    <div slot="params">
        <li>
            <code>offset</code><br />
            Access to the memory object must be synchronized externally. To assign
            a range of a memory object, the initial offset in bytes must be specified
            in offset.<br />
            To map the entire memory object, this must be <code>0</code>.
        </li>
        <li>
            <code>size</code><br />
            Access to the memory object must be synchronized externally. To allocate
            a range of a memory object, the size in bytes must be specified.<br
            />
            To map the entire memory object, it must be
            <code>VK_WHOLE_SIZE</code>
        </li>
    </div>
    <span slot="return">
        If successful, it returns a pointer to the mapped area. This pointer can
        then be cast to the appropriate type in the application and dereferenced
        to read and write the device memory directly.
    </span>
    <span slot="throws">
        <code>std::runtime_error</code> if the Memory failed to map.
    </span>
</MethodDescription>

<style lang="scss">
</style>
