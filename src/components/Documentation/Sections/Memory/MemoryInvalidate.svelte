<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import Reference from "$components/Documentation/Reference.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight language={cppHighlight} code={`void invalidate();`} />
<MethodDescription>
    <span slot="details">
        Invalidate a mapped memory range.<br />
        If <code>VK_MEMORY_PROPERTY_HOST_COHERENT_BIT</code> is not set in the
        memory properties of a mapped memory region, it is the responsibility of
        the application to explicitly clear or invalidate any caches that may be
        affected by the application.<br />
        An invalidation is needed if the device is writing to a mapped memory region
        and the host needs to see the effect of the device's writes.
    </span>
    <div slot="params">
        <li>
            <code>offset</code><br />
            The offset of the range of mapped memory to be invalidated. To invalidate
            the entire memory area, this must be <code>0</code>
        </li>
        <li>
            <code>size</code><br />
            The size of the mapped memory range to be invalidated. To invalidate
            the entire memory area, it must be <code>VK_WHOLE_SIZE</code>.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the mapped memory range failed to invalidate.
    </span>
</MethodDescription>

<style lang="scss">
</style>
