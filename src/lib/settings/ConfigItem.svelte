<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import FaLock from 'svelte-icons/fa/FaLock.svelte';
	import { Button, Dropdown, DropdownItem, Chevron } from 'flowbite-svelte';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';

	export let name = '???';
	export let values = [{ name: '???', id: 0 }];
	export let locked = false;
	export let selection: number;
	export let tag = 0;

	let dropdownOpen = false;

	const dispatch = createEventDispatcher<{select:ActionEvent}>();

	$: displayName = displayedName(selection);

	function displayedName(tag: number): string {
		let value = values.find((o) => o.id === tag);
		// console.log('Found name ' + (value == undefined ? '???' : value.name));
		return value == undefined ? '???' : value.name;
	}

	const handleClick = (e: MouseEvent, value: number) => {
		e.preventDefault();
		dropdownOpen = false;
		console.log('Click: id = ' + value + ' tag = ' + tag);
		dispatch('select', { tag: tag, value: value });
	};
</script>

<div class="py-0.5 px-0">
	<div class="w-full flex text-xl space-x-1 justify-between items-center">
		<div class="border-0 bg-blue-400/20 w-full h-12 flex flex-col justify-center">
			<div class="p-4 text-xl text-blue-200 flex items-center">
				{#if locked}
					<div class="border-0 mr-3 h-6 w-6"><FaLock /></div>
				{/if}
				<div class="border-0">{name}</div>
			</div>
		</div>
		<div class="border-0 bg-blue-400/20 h-12">
			{#if locked}
				<Button disabled class="!bg-transparent !text-xl !text-blue-200 flex"
					><div class="w-64">{displayName}</div>
					<div class="w-4 mr-2" /></Button
				>
			{:else}
				<Button class="!bg-transparent !text-xl !text-blue-200"
					><Chevron><div class="w-64">{displayName}</div></Chevron></Button
				>
				<Dropdown frameClass="!bg-slate-600" bind:open={dropdownOpen}>
					{#each values as { name, id }, i}
						<DropdownItem
							on:click={(e) => handleClick(e, id)}
							defaultClass="font-medium py-2 px-4 text-xl text-blue-200 bg-slate-600 hover:bg-slate-500"
							><div class="" id={id.toString()}>{name}</div></DropdownItem
						>
					{/each}
				</Dropdown>
			{/if}
		</div>
	</div>
</div>
