<script lang="ts">
    import Anchor from "$components/Documentation/Anchor.svelte";
    import MethodDescription from "$components/Documentation/MethodDescription.svelte";
    import { SectionID } from "$objects/Documentation/Section";
    import { getState } from "$stores/StateStore";
    import { Highlight } from "svelte-highlight";

    import cppHighlight from "svelte-highlight/languages/cpp";
</script>

<Highlight
    language={cppHighlight}
    code={`void createSurface(Instance* pInstance);`}
/>
<MethodDescription>
    <span slot="details">
        Create a <Anchor
            href="https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceKHR.html"
            target="_blank">Vulkan Surface</Anchor
        > using the <Anchor
            href="{getState().URL.documentation}#{SectionID.INSTANCE}"
            >Instance</Anchor
        >.
    </span>
    <div slot="params">
        <li>
            <code>pInstance</code><br />
            A pointer to the <Anchor
                href="{getState().URL.documentation}#{SectionID.INSTANCE}"
                >Instance</Anchor
            > to create a surface in.
        </li>
    </div>
    <span slot="throws">
        <code>std::runtime_error</code> if the surface failed to be created.
    </span>
</MethodDescription>

<style lang="scss">
</style>
