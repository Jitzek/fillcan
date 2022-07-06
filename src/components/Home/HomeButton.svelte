<script lang="ts">
    export let backgroundColor: "red" | "blue";

    let backgroundColorStyle = "";
    switch (backgroundColor) {
        case "red":
            backgroundColorStyle = "#b94f47";
            break;
        case "blue":
            backgroundColorStyle = "#787cbb";
            break;
    }
</script>

<button style="background-color: {backgroundColorStyle};"
    ><div class="icon"><slot name="icon" /></div>
    <div class="label"><slot name="label" /></div></button
>

<style lang="scss">
    button {
        font-family: $--font-family-input;
        color: $--input-fg-color-primary;

        border: none;
        border-radius: 1rem;
        width: 35%;
        max-width: 10rem;
        margin: 0.5rem;
        height: auto;
        aspect-ratio: 1 / 1;

        cursor: pointer;

        .icon {
            margin-bottom: 0.5rem;
        }

        .label {
            font-size: 1rem;
        }
    }
</style>
