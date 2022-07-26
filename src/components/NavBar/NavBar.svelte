<script lang="ts">
    import { fly } from "svelte/transition";
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";
    import HamburgerMenuIcon from "$components/NavBar/HamburgerMenuIcon.svelte";

    class RouteObject {
        public url: string;
        public label: string;
    }

    const routes: Array<RouteObject> = [
        {
            url: `${getState().URL.root}/`,
            label: "Home",
        },
        {
            url: `${getState().URL.root}/documentation`,
            label: "Documentation",
        },
        // TODO:
        // {
        //     url: `${getState().URL.root}/examples`,
        //     label: "Examples",
        // },
    ];

    let showHamburgerMenu = false;

    function handleHamburgerMenuClick(e: MouseEvent) {
        showHamburgerMenu = !showHamburgerMenu;
    }
</script>

<div
    class="navbar {$stateStore.Screen.displayType === DisplayType.MOBILE
        ? 'mobile'
        : 'desktop'}"
>
    <div class="logo-container">
        <img
            class="paint-trail-image"
            src="{getState().URL.root}/images/paint-trail.svg"
            alt="Paint"
        />
        <a href="{getState().URL.root}/">
            <img
                class="fillcan-logo"
                src="{getState().URL.root}/images/fillcan-logo-no-text.png"
                alt="Fillcan Logo"
            />
        </a>
    </div>
    {#if $stateStore.Screen.displayType === DisplayType.MOBILE}
        <div class="routes mobile">
            <button
                on:click={handleHamburgerMenuClick}
                class="hamburger-menu-button {showHamburgerMenu
                    ? 'activated'
                    : ''}"
            >
                <HamburgerMenuIcon />
            </button>

            {#if showHamburgerMenu}
                <div
                    in:fly={{ y: -10, duration: 500, opacity: 0 }}
                    out:fly={{ y: -20, duration: 250, opacity: 0 }}
                    class="routes-list-container"
                >
                    <ul class="routes-list">
                        {#each routes as route}
                            <li class="routes-list-item">
                                <a
                                    href={route.url}
                                    on:click={() => (showHamburgerMenu = false)}
                                    ><button>{route.label}</button></a
                                >
                            </li>
                        {/each}
                    </ul>
                </div>
            {/if}
        </div>
    {:else}
        <div class="routes desktop">
            <ul class="routes-list">
                {#each routes as route}
                    <li class="routes-list-item">
                        <a href={route.url}><button>{route.label}</button></a>
                    </li>
                {/each}
            </ul>
        </div>
    {/if}
</div>

<style lang="scss">
    .navbar {
        box-shadow: 0 5px 5px #333333ff;
        width: 100%;
        height: $--navbar-height;
        background-color: $--bg-color-primary;
        position: sticky;
        top: 0;
        z-index: 9;

        .logo-container {
            width: auto;
            height: 100%;

            .paint-trail-image {
                width: auto;
                height: 100%;
                position: absolute;
                z-index: 1;
            }

            .fillcan-logo {
                width: auto;
                height: calc($--navbar-height / 1.5);
                position: absolute;
                top: calc($--navbar-height / 6);
                left: calc($--navbar-height / 7);
                z-index: 2;
            }
        }

        .routes.mobile {
            .hamburger-menu-button {
                width: 2rem;
                height: 2rem;
                position: absolute;
                right: 1rem;
                top: calc($--navbar-height - ($--navbar-height / 2) - 1rem);
                padding: 0;
                margin: 0;
                border: none;
                background: none;
                cursor: pointer;
                fill: $--input-fg-color-secondary;
                transition: all 0.25s;
            }
            .hamburger-menu-button:hover,
            .hamburger-menu-button:focus,
            .hamburger-menu-button:active {
                fill: $--input-fg-color-primary;
            }
            .hamburger-menu-button.activated {
                width: 2.25rem;
                height: 2.25rem;
                top: calc($--navbar-height - ($--navbar-height / 2) - 1.1rem);
                right: 0.875rem;
                fill: $--input-fg-color-primary;
            }
            .routes-list-container {
                box-shadow: 0px 5px 5px #333333ff;
                background-color: $--bg-color-primary;

                .routes-list {
                    list-style: none;
                    text-decoration: none;
                    font-family: $--font-family-input;
                    padding: 0;
                    margin: 0;

                    button {
                        color: $--input-fg-color-primary;
                        background-color: $--input-bg-color-primary;
                        border: none;
                        width: 100%;
                        cursor: pointer;
                        height: calc($--navbar-height / 2);
                        transition: background-color 0.25s;
                        font-size: 1rem;
                        font-family: $--font-family-input;
                    }
                    button:hover,
                    button:focus,
                    button:active {
                        background-color: $--input-bg-color-secondary;
                    }
                }
            }
        }

        .routes.desktop {
            margin: 0 auto;
            margin-top: calc($--navbar-height - ($--navbar-height / 2) - 1.5rem);
            .routes-list {
                display: flex;
                list-style: none;
                text-decoration: none;
                font-family: $--font-family-input;
                padding: 0;
                margin: 0;
                overflow: hidden;

                button {
                    color: $--fg-color-primary;
                    background-color: $--input-bg-color-primary;
                    border: none;
                    width: 100%;
                    cursor: pointer;
                    height: 3rem;
                    transition: background-color 0.25s;
                    font-size: 1rem;
                    font-family: $--font-family-input;
                    width: 22.5vw;
                    max-width: 15rem;
                }
                button:hover,
                button:focus,
                button:active {
                    background-color: $--input-bg-color-secondary;
                }
            }
        }
    }

    .navbar.desktop {
        display: flex;
        vertical-align: middle;
        align-content: center;
    }
</style>
