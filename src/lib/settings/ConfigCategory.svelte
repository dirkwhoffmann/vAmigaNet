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

<Button on:click color="transparent" class="!p-0"><div class="text-3xl">{name}</div></Button>
