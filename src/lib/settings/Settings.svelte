<script lang="ts">
	import { Button, Dropdown, DropdownItem, DropdownDivider, DropdownHeader, Chevron } from 'flowbite-svelte';
</script>

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
