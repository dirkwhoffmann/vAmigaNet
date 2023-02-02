<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import {
		Button,
		Dropdown,
		DropdownItem,
		DropdownDivider,
		DropdownHeader,
		Chevron
	} from 'flowbite-svelte';

	export let name = '???';
	// export let value = 'undefined';
	export let selectedTag: number; 

	const bgcolor = 'bg-slate-600';

	export let values = [
		{ name: 'Old OCS', id: 0 },
		{ name: 'New OCS', id: 1 },
		{ name: 'Old ECS', id: 2 },
		{ name: 'New ECS', id: 3 }
	];
	const dispatch = createEventDispatcher();

	$: selection = displayedName(selectedTag); 

	function displayedName(tag: number): string {
		let value = values.find(o => o.id === tag);
		console.log("Found name " + (value == undefined ? "???" : value.name));
		return value == undefined ? "???" : value.name; 
	}

	const handleClick = (e: MouseEvent) => {
		e.preventDefault();
		console.log('Click: id = ' + e.target!.id);
		dispatch('select', {
			text: e.target!.id
		});
	};
</script>

<div class="py-0.5 px-0">
	<div class="w-full flex text-xl space-x-1 justify-between items-center">
		<div class="border-0 bg-blue-400/20 w-full h-12 flex flex-col justify-center">
			<div class="p-4 text-xl text-blue-200">{name}</div>
		</div>
		<div class="border-0 bg-blue-400/20 h-12">
			<Button color="" class="!text-xl !text-blue-200"
				><Chevron><div class="w-64">{selection}</div></Chevron></Button
			>
			<Dropdown frameClass="!{bgcolor}">
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
