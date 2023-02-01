<script lang="ts">
	import {
		Button,
		Dropdown,
		DropdownItem,
		DropdownDivider,
		DropdownHeader,
		Chevron
	} from 'flowbite-svelte';

    export let name = "???";
</script>

<div class="py-0.5 px-10">
	<div class="p-1 bg-gray-400/20 w-full flex text-2xl justify-between items-center">
		<div class="">{name}</div>
		<Button color="transparent" class="!text-2xl"><Chevron>Dropdown button</Chevron></Button>
		<Dropdown>
			<DropdownItem>Old OCS</DropdownItem>
			<DropdownItem>New OCS</DropdownItem>
			<DropdownItem>ECS 1MB</DropdownItem>
			<DropdownItem>ECS 2MB</DropdownItem>
		</Dropdown>
	</div>
</div>

<!--
<div class="p-16 z-50">
    <Button class="font-sofia-semi !bg-gray-100/20" pill={true}><Chevron>Dropdown button</Chevron></Button>
    <Button color="green"><Chevron>Dropdown button</Chevron></Button>
    <Dropdown>
        <DropdownItem>Dashboard</DropdownItem>
        <DropdownDivider />
        <DropdownItem>Settings</DropdownItem>
        <DropdownItem>Earnings</DropdownItem>
        <DropdownItem slot="footer">Separated link</DropdownItem>
    </Dropdown>
</div>
-->
