<script lang="ts">
    import { createEventDispatcher } from 'svelte';
    import type { ActionEvent } from '$lib/types';

    export let tag = 0;
    export let value = 0;
    export let locked = false;
    export let min = 0;
    export let max = 0;
    export let open = true;

    const dispatch = createEventDispatcher<{ select: ActionEvent }>();

    function sliderAction(e: InputEvent)
    {
        e.preventDefault();
        value = Number((e.target as HTMLInputElement).value);
        dispatch('select', {tag: tag, value: value});
    }

</script>

<div class="dropdown dropdown-bottom">
    <!-- Make DropDown work in Safari using the label / tabindex trick (see DaisyUI doc) -->
    <!-- svelte-ignore a11y-no-noninteractive-tabindex -->
    <!-- svelte-ignore a11y-label-has-associated-control -->
    <label tabindex="0" on:click={(e) => open = true} class={locked ? 'pointer-events-none' : ''}>
        <slot/>
    </label>
    <!-- svelte-ignore a11y-no-noninteractive-tabindex -->
    {#if open}
        <ul tabindex="0" class="dropdown-content menu bg-base-100 text-base-content w-full mt-1">
            <input
                    type="range"
                    on:input={(e) => sliderAction(e)}
                    on:mouseup={() => open = false}
                    {min}
                    {max}
                    {value}
                    class="range range-accent h-12 px-4 rounded-none"
            />
        </ul>
    {/if}
</div>
