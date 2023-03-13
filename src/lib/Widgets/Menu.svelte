<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import type { ActionEvent, MenuItem } from '$lib/types';
	import { MenuSeparator } from '$lib/types';
	import Checkmark from './Checkmark.svelte';

	// Menu identifier
	export let tag = 0;

	// Menu items
	export let items: MenuItem[] = [];
	$: selectedItems = items.filter((item) => item.isSelected);

	// State
	export let isEnabled = true;

	// Visual appearance
	export let dropdownStyle = '';
	export let listStyle = '';

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	const action = (e: MouseEvent, value: number) => {
		e.preventDefault();

		// Force the dropdown to close
		if (document.activeElement) (document.activeElement as HTMLElement).blur();

		dispatch('select', { tag: tag, value: value });
	};

	function style(i: number) {
		return items[i].isEnabled ? '' : 'opacity-20';
	}
</script>

<div class="dropdown {dropdownStyle}">
	<!-- Make DropDown work in Safari using the label / tabindex trick (see DaisyUI doc) -->
	<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
	<!-- svelte-ignore a11y-label-has-associated-control -->
	<label tabindex="0" class={isEnabled ? '' : 'pointer-events-none'}>
		<slot />
	</label>
	<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
	<ul tabindex="0" class="dropdown-content menu bg-base-100 text-base-content {listStyle}">
		{#key items}
			{#each items as item, i}
				{#if item instanceof MenuSeparator}
					<li class="divider"></li>
				{:else if !item.isHidden}
					<li id={tag.toString()}>
						<button
							disabled={!item.isEnabled}
							class={item.isEnabled ? '' : 'hover:bg-base-100 opacity-40'}
							on:click={(e) => action(e, item.tag)}
						>
							<Checkmark enabled={selectedItems.length !== 0} visible={item.isSelected} />
							{item.title}</button
						>
					</li>
				{/if}
			{/each}
		{/key}
	</ul>
</div>
