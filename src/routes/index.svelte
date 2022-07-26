<script lang="ts">
    import { base } from "$app/paths";

    import HomeButton from "$components/Home/HomeButton.svelte";
    import DocumentationIcon from "$components/svg/DocumentationIcon.svelte";
    import GitHubIcon from "$components/svg/GitHubIcon.svelte";
    import { DisplayType } from "$objects/State";

    import { getState, stateStore } from "$stores/StateStore";
</script>

<div
    class="home-container {$stateStore.Screen.displayType === DisplayType.MOBILE
        ? 'mobile'
        : 'desktop'}"
>
    <div class="big-picture-container">
        <div
            class="big-picture"
            style="--background-url: url({base}/images/home/fillcan_thumbnail.png);"
        />
    </div>
    <div class="main-overlay">
        <div class="home-buttons-container">
            <a href="https://github.com/Jitzek/fillcan" target="_blank">
                <HomeButton backgroundColor="red">
                    <div class="icon-container" slot="icon">
                        <GitHubIcon />
                    </div>
                    <div slot="label">Visit Repository</div>
                </HomeButton>
            </a>
            <a href="{base}/documentation">
                <HomeButton backgroundColor="blue">
                    <div class="icon-container" slot="icon">
                        <DocumentationIcon />
                    </div>
                    <div slot="label">Documentation</div>
                </HomeButton>
            </a>
        </div>

        <div class="short-introduction-container">
            <h1>About</h1>
            Fillcan is a C++20 library for rendering graphics using Vulkan.<br
            /><br />
            Fillcan aims to be a object-oriënted solution for communication with
            the Vulkan API. It's main goals are as follows:
            <ul class="main-goals">
                <li>
                    Decrease the boilerplate code needed for talking with
                    Vulkan.
                </li>
                <li>
                    Handle the allocation and deallocation of memory within the
                    objects that require it. Automatically deallocate memory
                    once the object goes out of scope.
                </li>
                <li>
                    Don't take away control from the application. Allow as many
                    parameters to be tweaked by the application that implements
                    the library.
                </li>
            </ul>
        </div>
        <div style="padding-bottom: 5rem;" />
    </div>
</div>

<style lang="scss">
    .home-container {
        .big-picture-container {
            background-color: $--bg-color-secondary;
            position: fixed;
            height: 20rem;
            width: 100%;
            .big-picture {
                background: var(--background-url);
                background-size: contain;
                background-repeat: no-repeat;
                background-position: 50%;
                overflow: hidden;
                width: inherit;
                height: inherit;
                z-index: 0;
            }
        }

        .main-overlay {
            background-color: $--bg-color-primary;
            transform: translateY(20rem);
            min-height: calc(100vh - 5rem); // 5rem is the height of the NavBar
            width: 100%;
            overflow-y: scroll;
            z-index: 1;
            box-shadow: 0 -5px 5px #333333ff;

            .home-buttons-container {
                margin-top: 1rem;
                .icon-container {
                    fill: $--input-fg-color-primary;
                    width: 5rem;
                    margin: 0 auto;
                    height: 5rem;
                }
                text-align: center;
            }

            .short-introduction-container {
                margin-top: 2rem;
                font-family: $--font-family-default;
                color: $--fg-color-primary;
                font-size: 1rem;
                padding: 0 20vw 0 20vw;

                .main-goals {
                    margin: 0;
                    // list-style: "- ";
                }
            }
        }
    }

    .home-container.mobile {
        .short-introduction-container {
            padding: 0 10vw 0 10vw;
        }
    }
</style>
