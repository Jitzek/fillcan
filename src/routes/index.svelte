<script lang="ts">
    import HomeButton from "$components/Home/HomeButton.svelte";
    import DocumentationIcon from "$components/svg/DocumentationIcon.svelte";
    import GitHubIcon from "$components/svg/GitHubIcon.svelte";
    import { DisplayType } from "$objects/State";

    import { getState, stateStore } from "$stores/StateStore";
</script>

<div class="home-container">
    <div class="big-picture-container">
        <div
            class="big-picture"
            style="--background-url: url({getState().URL
                .root}/images/home/fillcan_thumbnail.png);"
        />
    </div>
    <div class="main-overlay">
        <div class="home-buttons-container">
            <HomeButton backgroundColor="red">
                <div class="icon-container" slot="icon">
                    <GitHubIcon />
                </div>
                <div slot="label">Visit Repository</div>
            </HomeButton>
            <HomeButton backgroundColor="blue">
                <div class="icon-container" slot="icon">
                    <DocumentationIcon />
                </div>
                <div slot="label">Documentation</div>
            </HomeButton>
        </div>

        <div class="short-introduction-container">
            Fillcan is a C++20 library for rendering graphics using Vulkan. <br
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
            min-height: calc(100vh - 7rem); // 7rem == height of NavBar
            width: 100%;
            overflow-y: scroll;
            z-index: 1;

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
                padding: 0.5rem;

                .main-goals {
                    margin: 0;
                    list-style: '- ';
                }
            }
        }
    }
</style>
