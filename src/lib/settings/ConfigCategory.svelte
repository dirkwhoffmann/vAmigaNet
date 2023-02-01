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

<Button color="blue" class="!p-0"><div class="text-3xl">{name}</div></Button>
