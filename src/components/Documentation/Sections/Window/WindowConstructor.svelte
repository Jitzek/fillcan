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
    code={`Window(unsigned int width, unsigned int height, std::string name);`}
/>
<MethodDescription>
    <span slot="details">
        Create a new Window.<br />
        Creates a new <Anchor href="https://www.glfw.org/" target="_blank"
            >GLFW</Anchor
        > Window.
    </span>
    <div slot="params">
        <li>
            <code>width</code><br />
            The initial width of the Window.
        </li>
        <li>
            <code>height</code><br />
            The initial height of the Window.
        </li>
        <li>
            <code>name</code><br />
            The name of the Window.
        </li>
    </div>
</MethodDescription>

<style lang="scss">
</style>
