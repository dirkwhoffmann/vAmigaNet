<script lang="ts">
	import {
		Button,
		Dropdown,
		DropdownItem,
		DropdownDivider,
		DropdownHeader,
		Chevron
	} from 'flowbite-svelte';

	export let name = '???';

	function doClick1(arg) {
		console.log('Click Clack 1 ' + arg);
	}
	function doClick2(arg) {
		console.log('Click Clack 2' + arg);
	}
</script>

<div class="py-0.5 px-0">
	<div class="pl-5 bg-blue-400/20 w-full flex text-xl justify-between items-center">
		<div class="text-xl text-blue-200">{name}</div>
		<Button color="transparent" class="!text-xl !text-blue-200"
			><Chevron>Dropdown button</Chevron></Button
		>
		<Dropdown>
			<DropdownItem id="Waldfee" on:click={doClick1("Hallo")}>Old OCS</DropdownItem>
			<DropdownItem on:click={doClick2("Huhu")}>New OCS</DropdownItem>
			<DropdownItem>ECS 1MB</DropdownItem>
			<DropdownItem>ECS 2MB</DropdownItem>
		</Dropdown>
	</div>
</div>
