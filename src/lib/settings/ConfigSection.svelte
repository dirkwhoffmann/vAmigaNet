<script lang="ts">
	import {
		Button,
	} from 'flowbite-svelte';

    export let name = "???";
</script>

<div class="px-0 py-0.5">
	<div class="bg-transparent w-full flex">
		<div class="text-xl">{name}</div>
	</div>
    <slot />
</div>
