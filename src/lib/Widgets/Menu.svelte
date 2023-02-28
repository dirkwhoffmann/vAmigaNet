<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import Chevron from '$lib/Settings/Chevron.svelte'; // TODO: MOVE TO widgets
	import type { ActionEvent } from '$lib/Settings/Settings.svelte'; // TODO: MOVE TO types.ts
	import type { MenuItem } from '$lib/types';

	export let tag = 0;
	export let values = [{ name: '???', id: 0 }];
	export let items: MenuItem[];
	export let selectedTag = 0;
	export let disabled = false;
	export let selectable = true;
	export let dropdownStyle = '';
	export let listStyle = '';
	export let title = '';

    $: selectedItems = items.filter(item => item.isSelected);

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
		{#each items as { title, tag, isHidden, isEnabled, isSelected }}
        {#if !isHidden}
				<li id={tag.toString()}>
					<button {disabled} class={disabledStyle} on:click={(e) => listAction(e, tag)}>
                        {#if selectedItems.length} 
							<div class="w-4">{@html isSelected ? '&#10003' : ''}</div>
						{/if}
						{title}</button
					>
				</li>
			{/if}
		{/each}
	</ul>
</div>
