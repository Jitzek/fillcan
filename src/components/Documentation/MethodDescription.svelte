{#if $$slots.details}
    <div class="details">
        <slot name="details" />
    </div>
{/if}
{#if $$slots.params}
    <ul class="method-description">
        <div class="params">
            <slot name="params" />
        </div>
    </ul>
{/if}
{#if $$slots.return}
    <div class="return">
        <code>@return</code>: <slot name="return" />
    </div>
{/if}
{#if $$slots.throws}
    <div class="throws">
        <code>@throws</code>: <slot name="throws" />
    </div>
{/if}
{#if $$slots.note}
    <div class="note">
        <code>@note</code>: <slot name="note" />
    </div>
{/if}

<style lang="scss">
    .details {
        font-size: 1rem;
        margin: 0;
        padding: 0;
    }
    .method-description {
        .params {
            font-size: 1rem;
            :global(code) {
                background-color: $--bg-color-secondary;
            }
            :global(li) {
                margin-bottom: 0.5rem;
            }
        }
    }
    .return {
        font-size: 1rem;
        code {
            background-color: $--bg-color-secondary;
        }
    }
    .throws {
        font-size: 1rem;
        code {
            background-color: $--bg-color-secondary;
        }
    }
    .note {
        margin-top: 1rem;
        background-color: $--bg-color-secondary;
        font-size: 1rem;
    }
</style>
