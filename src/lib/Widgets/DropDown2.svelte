<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import Chevron from '$lib/Settings/Chevron.svelte'; // TODO: MOVE TO widgets
	import type { ActionEvent } from '$lib/Settings/Settings.svelte'; // TODO: MOVE TO types.ts

	export let tag = 0;
	export let values = [{ name: '???', id: 0 }];
	export let selectedTag = 0;
	export let disabled = false;
	export let selectable = true;
	export let dropdownStyle = '';
	export let listStyle = '';
	export let title = '';

	$: disabledStyle = disabled ? 'hover:bg-base-100 opacity-30' : '';

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	$: displayName = title == '' ? displayedName(selectedTag) : title;
	function displayedName(selectedTag: number): string {
		if (title != '') return title;
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

<div class="dropdown {dropdownStyle}">
	<!-- Make DropDown work in Safari using the label / tabindex trick (see DaisyUI doc) -->
	<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
	<!-- svelte-ignore a11y-label-has-associated-control -->
	<label tabindex="0">
		<slot />
	</label>
	<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
	<ul tabindex="0" class="dropdown-content menu bg-base-100 text-base-content {listStyle}">
		{#each values as { name, id }, i}
			<li id={id.toString()}>
				<button {disabled} class={disabledStyle} on:click={(e) => listAction(e, id)}>
					{#if selectable}
						<div class="w-4">{@html selectedTag == id ? '&#10003' : ''}</div>
					{/if}
					{name}</button
				>
			</li>
		{/each}
	</ul>
</div>
