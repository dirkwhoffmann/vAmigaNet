<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import FaLock from 'svelte-icons/fa/FaLock.svelte';
	import {
		Button,
		Dropdown,
		DropdownItem,
		DropdownDivider,
		DropdownHeader,
		Chevron
	} from 'flowbite-svelte';

	export let name = '???';
	export let values = [{ name: '???', id: 0 }];
	export let locked = false;
	export let selection: number;

	const bgcolor = 'bg-slate-600';
	let dropdownOpen = false;

	const dispatch = createEventDispatcher();

	$: displayName = displayedName(selection);

	function displayedName(tag: number): string {
		let value = values.find((o) => o.id === tag);
		// console.log('Found name ' + (value == undefined ? '???' : value.name));
		return value == undefined ? '???' : value.name;
	}

	const handleClick = (e: MouseEvent) => {
		e.preventDefault();
		dropdownOpen = false;
		console.log('Click: id = ' + e.target!.id);
		dispatch('select', {
			text: e.target!.id
		});
	};
</script>

<div class="py-0.5 px-0">
	<div class="w-full flex text-xl space-x-1 justify-between items-center">
		<div class="border-0 bg-blue-400/20 w-full h-12 flex flex-col justify-center">
			<div class="p-4 text-xl text-blue-200 flex items-center">
				{#if locked}
				<div class="border-0 mr-3 h-6"><FaLock /></div>
				{/if}
				<div class="border-0">{name}</div>
			</div>
		</div>
		<div class="border-0 bg-blue-400/20 h-12">
			<Button color="" class="!text-xl !text-blue-200"
				><Chevron><div class="w-64">{displayName}</div></Chevron></Button
			>
			<Dropdown frameClass="!{bgcolor}" bind:open={dropdownOpen}>
				{#each values as { name, id }, i}
					<DropdownItem
						on:click={handleClick}
						defaultClass="font-medium py-2 px-4 text-xl text-blue-200 {bgcolor} hover:bg-slate-500"
						><div class="" id={id.toString()}>{name}</div></DropdownItem
					>
				{/each}
			</Dropdown>
		</div>
	</div>
</div>
