<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import type { ActionEvent } from '$lib/types';
    import { activeSlider } from '$lib/stores';

	export let tag = 0;
	export let selectedTag = 0;
	export let locked = false;
	export let min = 0;
	export let max = 0;

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	const sliderAction = (e: Event) => {
		e.preventDefault();
		selectedTag = e.target!.value;
		console.log('slider: ', tag, selectedTag);
		dispatch('select', { tag: tag, value: selectedTag });
	};
</script>

{#if locked}
	<button
		class="btn btn-primary hover:bg-primary w-[18rem] border-0 rounded-none text-xl font-normal opacity-50"
		>{selectedTag.toString()}</button
	>
{:else if $activeSlider == tag}
	<ul class="menu w-[18rem] bg-primary">
		<input
			type="range"
			on:input={(e) => sliderAction(e)}
			on:click={() => console.log('Click')}
            on:mouseup={() => console.log('mouseup')}
			{min}
			{max}
			value={selectedTag}
			class="range range-accent h-12 px-4 rounded-none"
		/>
	</ul>
{:else}
	<button
        on:click={() => $activeSlider = tag} 
		class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal"
		>{selectedTag.toString()}
	</button>
{/if}
