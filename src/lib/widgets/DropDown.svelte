<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import Chevron from '$lib/settings/Chevron.svelte'; // TODO: MOVE TO widgets
	import type { ActionEvent } from '$lib/settings/Settings.svelte'; // TODO: MOVE TO types.ts
    
	// General options
	export let tag = 0;
	export let locked = false;

	// DropDown list options
	export let values = [{ name: '???', id: 0 }];
	export let selectedTag = 0;

	// DropDown slider options
	export let min = 0;
	export let max = 0;

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();
    
	$: displayName = displayedName(selectedTag);
	function displayedName(selectedTag: number): string {
		if (min != max) {
			return tag.toString();
		} else {
			for (const value of values) {
				if (value.id == selectedTag) return value.name;
			}
            return '???';
		}
	}

	const listAction = (e: MouseEvent, value: number) => {
		e.preventDefault();
		const elem = document.activeElement;

		selectedTag = value;

		// Hack to close the dropdown when an item was selected
		if (elem) {
			elem?.blur();
		}

		console.log('tag: ', tag, 'selectedTag: ', selectedTag);
		dispatch('select', { tag: tag, value: value });
	};

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
{:else if min != max}
	<ul class="dropdown-content menu w-[18rem] bg-primary">
		<input
			type="range"
			on:input={(e) => sliderAction(e)}
			on:click={(e) => console.log('Click')}
			min="0"
			max="100"
			value={selectedTag}
			class="range range-accent h-12 px-4 rounded-none"
		/>
	</ul>
{:else}
	<div class="dropdown dropdown-end">
		<button class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal"
			><Chevron>{displayName}</Chevron>
		</button>
		<ul class="dropdown-content menu p-2 text-xl bg-accent w-[18rem]">
			{#each values as { name, id }, i}
				<li class="" id={id.toString()}>
					<button class="bg-accent text-accent-content" on:click={(e) => listAction(e, id)}
						><div class="w-4">{@html selectedTag == id ? '&#10003' : ''}</div>
						{name}</button
					>
				</li>
			{/each}
		</ul>
	</div>
{/if}
