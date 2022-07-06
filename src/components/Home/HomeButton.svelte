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

<button class={backgroundColor}
    ><div class="icon"><slot name="icon" /></div>
    <div class="label"><slot name="label" /></div></button
>

<style lang="scss">
    button {
        font-family: $--font-family-input;
        color: $--input-fg-color-primary;

        border: none;
        border-radius: 1rem;
        width: 10rem;
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

        .icon,
        .label {
            transition: transform 0.25s ease-in-out;
        }
    }

    button:hover,
    button:focus,
    button:active {
        .label,
        .icon {
            transform: scale(1.1);
        }
    }

    button.red {
        background-color: #b94f47;
        transition: background-color 0.25s ease-in-out;
    }
    button.red:hover,
    button.red:focus,
    button.red:active {
        background-color: #b94038;
    }

    button.blue {
        background-color: #787cbb;
        transition: background-color 0.25s ease-in-out;
    }
    button.blue:hover,
    button.blue:focus,
    button.blue:active {
        background-color: #696ebb;
    }
</style>
