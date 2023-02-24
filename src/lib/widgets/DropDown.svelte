<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import Chevron from '$lib/settings/Chevron.svelte'; // TODO: MOVE TO widgets
	import type { ActionEvent } from '$lib/settings/Settings.svelte'; // TODO: MOVE TO types.ts

	export let locked = false;
	export let values = [{ name: '???', id: 0 }];
	export let tag = 0;
	export let selectedTag = 0;

    const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	$: displayName = displayedName(selectedTag);

	function displayedName(selectedTag: number): string {
		for (const value of values) {
			if (value.id == selectedTag) return value.name;
		}
		return '???';
	}

	const handleClick = (e: MouseEvent, value: number) => {
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
</script>

{#if locked}
	<button class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal opacity-50"
		>{displayName}</button
	>
{:else}
	<div class="dropdown dropdown-end">
		<button class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal"
			><Chevron>{displayName}</Chevron>
		</button>
		<ul class="dropdown-content menu p-2 text-xl bg-accent w-[18rem]">
			{#each values as { name, id }, i}
				<li class="" id={id.toString()}>
					<button class="bg-accent text-accent-content" on:click={(e) => handleClick(e, id)}
						><div class="w-4">{@html selectedTag == id ? '&#10003' : ''}</div>
						{name}</button
					>
				</li>
			{/each}
		</ul>
	</div>
{/if}
