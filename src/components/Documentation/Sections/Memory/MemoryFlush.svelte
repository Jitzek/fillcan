<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void unmap();`} />
<MethodDescription>
    <span slot="details">
        Flush a mapped memory range.<br />
        If <code>VK_MEMORY_PROPERTY_HOST_COHERENT_BIT</code> is not set in the
        memory properties of a mapped memory region, it is the responsibility of
        the application to explicitly flush or invalidate any caches that may be
        affected by the application.<br />
        A flush is needed if the host has written to an allocated memory region and
        wants the device to see the effect of those writes.
    </span>
    <div slot="params">
        <li>
            <code>offset</code><br />
            The offset of the range of mapped memory to be flushed. To flush the
            entire memory area, this must be <code>0</code>
        </li>
        <li>
            <code>size</code><br />
            The size of the mapped memory range to be flushed. To flush the entire
            memory area, it must be <code>VK_WHOLE_SIZE</code>.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the mapped memory range failed to flush.
    </span>
</MethodDescription>

<style lang="scss">
</style>
