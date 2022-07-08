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
{#if $$slots.returns}
    <div class="returns">
        <code>@returns</code>: <slot name="returns" />
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
    .returns {
        font-size: 1rem;
        code {
            background-color: $--bg-color-secondary;
        }
    }
</style>
