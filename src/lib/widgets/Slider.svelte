<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import type { ActionEvent } from '$lib/settings/Settings.svelte'; // TODO: MOVE TO types.ts

	export let tag = 0;
    export let selectedTag = 0;
	export let locked = false;
	export let min = 0;
	export let max = 0;

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();
    
	$: displayName = displayedName(selectedTag);
	function displayedName(selectedTag: number): string {
			return tag.toString();
    }

	const sliderAction = (e: Event) => {
		e.preventDefault();
		dispatch('select', { tag: tag, value: e.target!.value });
	};
</script>

{#if locked}
	<button
		class="btn btn-primary hover:bg-primary w-[18rem] border-0 rounded-none text-xl font-normal opacity-50"
		>{displayName}</button
	>
{:else}
	<ul class="dropdown-content menu w-[18rem] bg-primary">
		<input
			type="range"
			on:input={(e) => sliderAction(e)}
			on:click={(e) => console.log('Click')}
			min={min}
			max={max}
			value={selectedTag}
			class="range range-accent h-12 px-4 rounded-none"
		/>
	</ul>
{/if}
