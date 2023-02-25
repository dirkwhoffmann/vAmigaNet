<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import Chevron from '$lib/Settings/Chevron.svelte'; // TODO: MOVE TO widgets
	import type { ActionEvent } from '$lib/Settings/Settings.svelte'; // TODO: MOVE TO types.ts

	export let tag = 0;
	export let values = [{ name: '???', id: 0 }];
	export let selectedTag = 0;
	export let locked = false;

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	$: displayName = displayedName(selectedTag);
	function displayedName(selectedTag: number): string {
		for (const value of values) {
			if (value.id == selectedTag) return value.name;
		}
		return '???';
	}

	const listAction = (e: MouseEvent, value: number) => {
		e.preventDefault();

		// Force the dropdown to close
		if (document.activeElement) (document.activeElement as HTMLElement).blur();

		selectedTag = value;
		dispatch('select', { tag: tag, value: value });
	};
</script>

{#if locked}
	<button
		class="btn btn-primary hover:bg-primary w-[18rem] border-0 rounded-none text-xl font-normal opacity-50"
		>{displayName}</button
	>
{:else}
	<div class="dropdown dropdown-end">
		<!-- Make DropDown work in Safari using the label / tabindex trick (see DaisyUI doc) -->
		<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
		<!-- svelte-ignore a11y-label-has-associated-control -->
		<label tabindex="0" class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal"
			><Chevron>{displayName}</Chevron>
		</label>
		<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
		<ul tabindex="0" class="dropdown-content menu p-2 text-xl bg-accent w-[18rem]">
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
