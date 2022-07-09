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
    code={`void mainLoop(std::function<void(double)> callback);`}
/>
<MethodDescription>
    <span slot="details">
        The main loop of the Fillcan Graphics API. The main loop of the Fillcan
        Graphics API gives access to a callback function with the deltaTime. The
        main loop calls this callback every frame.
    </span>
    <div slot="params">
        <li>
            <code>callback</code><br />
            The callback with the deltaTime which will be called every frame.
        </li>
    </div>
</MethodDescription><br />
Example:
<Highlight
    language={cppHighlight}
    code={`{
    ...
    fillcan.mainLoop(std::bind(&App::update, this, std::placeholders::_1));
}

void App::update(double deltaTime) {
    // Called every frame
}`}
/>
