<script lang="ts">
    import { DisplayType } from "$objects/State";
    import { getState, stateStore } from "$stores/StateStore";
    import HamburgerMenuIcon from "$components/NavBar/HamburgerMenuIcon.svelte";
</script>

<div class="navbar">
    <div class="logo-container">
        <img
            class="paint-trail-image"
            src="{getState().URL.root}/images/paint-trail.svg"
            alt="Paint"
        />
        <a href={getState().URL.root}>
            <img
                class="fillcan-logo"
                src="{getState().URL.root}/images/fillcan-logo-no-text.png"
                alt="Fillcan Logo"
            />
        </a>
    </div>
    {#if $stateStore.Screen.displayType === DisplayType.MOBILE}
        <div class="routes mobile">
            <button class="hamburger-menu-button">
                <HamburgerMenuIcon color="#eeeeee" size="1.5rem" />
            </button>
        </div>
    {:else}
        <div class="routes desktop" />
    {/if}
</div>

<style lang="scss">
    .navbar {
        width: 100%;
        height: 7rem;
        background-color: $--bg-color-primary;
        position: sticky;
        top: 0;
        filter: drop-shadow(0 5px 2.5px #333333ff);

        .logo-container {
            width: auto;
            height: 100%;

            .paint-trail-image {
                width: auto;
                height: 100%;
                position: absolute;
            }

            .fillcan-logo {
                width: auto;
                height: 4rem;
                position: absolute;
                top: 1.5rem;
                left: 1rem;
            }
        }

        .routes.mobile {
            .hamburger-menu-button {
                width: 2rem;
                height: 2rem;
                position: absolute;
                right: 1rem;
                top: 2.5rem;
                padding: 0;
                margin: 0;
                border: none;
                background: none;
                cursor: pointer;
            }
        }
    }
</style>
