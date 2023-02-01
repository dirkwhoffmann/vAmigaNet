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

    const dispatch = createEventDispatcher();
        
	const handleClick = (e: PointerEvent) => {
		e.preventDefault();
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
			<DropdownItem on:click={handleClick} id="Ernie">Old OCS</DropdownItem>
			<DropdownItem on:click={handleClick} id="Bert">New OCS</DropdownItem>
			<DropdownItem on:click={handleClick} id="Oskar">ECS 1MB</DropdownItem>
			<DropdownItem on:click={handleClick} id="Bibo">ECS 2MB</DropdownItem>
		</Dropdown>
	</div>
</div>
