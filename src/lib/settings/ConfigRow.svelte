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
	export let value = 'undefined';

	let values = [
		{ name: 'Old OCS', id: 0 },
		{ name: 'New OCS', id: 1 },
		{ name: 'Old ECS', id: 2 },
		{ name: 'New ECS', id: 3 },
	];
	const dispatch = createEventDispatcher();

	const handleClick = (e: PointerEvent) => {
		e.preventDefault();
        console.log("Click");
        console.log("ID = " + e.target!.id);
		dispatch('select', {
			text: e.target!.id
		});
	};
</script>

<div class="py-0.5 px-0">
	<div class="pl-5 bg-blue-400/20 w-full flex text-xl justify-between items-center">
		<div class="text-xl text-blue-200">{name}</div>
		<Button color="transparent" class="!text-xl !text-blue-200"><Chevron>{value}</Chevron></Button>
		<Dropdown>
            {#each values as { name, id }, i}
			<DropdownItem on:click={handleClick} id={id}>{name}</DropdownItem>
            {/each}
		</Dropdown>
	</div>
</div>
