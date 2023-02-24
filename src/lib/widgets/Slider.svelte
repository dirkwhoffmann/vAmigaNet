<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import type { ActionEvent } from '$lib/settings/Settings.svelte'; // TODO: MOVE TO types.ts
	import Chevron from '$lib/settings/Chevron.svelte';

	export let tag = 0;
	export let selectedTag = 0;
	export let locked = false;
	export let min = 0;
	export let max = 0;
	export let openAsDropdown = true;

	let isFocused = false;
	$: console.log('isFocuses = ', isFocused);

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

    /*
	$: displayName = displayedName(selectedTag);
	function displayedName(selectedTag: number): string {
		return tag.toString();
	}
    */

	$: dropDownOptions = openAsDropdown ? 'dropdown dropdown-end' : '';

	const sliderAction = (e: Event) => {
		e.preventDefault();
        selectedTag = e.target!.value; 
        console.log("slider: ", tag, selectedTag);
		dispatch('select', { tag: tag, value: selectedTag });
	};
</script>

{#if locked}
	<button
		class="btn btn-primary hover:bg-primary w-[18rem] border-0 rounded-none text-xl font-normal opacity-50"
		>{selectedTag.toString()}</button
	>
{:else if isFocused}
	<ul class="dropdown-content menu w-[18rem] bg-primary">
		<input
			type="range"
			on:input={(e) => sliderAction(e)}
			on:click={(e) => console.log('Click')}
			on:blur={() => (isFocused = false)}
			{min}
			{max}
			value={selectedTag}
			class="range range-accent h-12 px-4 rounded-none"
		/>
	</ul>
{:else}
	<button
		on:focus={() => (isFocused = true)}
		class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal"
		>{selectedTag.toString()}
	</button>
{/if}
