<script lang="ts">
	import { proxy, amiga, retroShell, layer, dfConnected } from '$lib/stores';
	import { Layer } from '$lib/types';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import DropZoneCell from './DropZoneCell.svelte';

	function insert(drive: number) {
		console.log("insert", drive);
		$layer = Layer.none;

	}
</script>

<div class="absolute top-10 left-0 w-screen flex justify-center" transition:fade>
	<div class="relative flex justify-center space-x-4 p-4 rounded-xl items-center" transition:fade>
			<DropZoneCell id={0} name="DF0" on:drive={ () => insert(0) } />
			<DropZoneCell id={1} name="DF1" on:drive={ () => insert(1) } />
			<DropZoneCell id={2} name="DF2" on:drive={ () => insert(2) } />
			<DropZoneCell id={3} name="DF3" on:drive={ () => insert(3) } />
	</div>
</div>
