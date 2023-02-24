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
			<DropZoneCell name="DF0" enabled={$dfConnected[0]} on:drive={ () => insert(0) } />
			<DropZoneCell name="DF1" enabled={$dfConnected[1]} on:drive={ () => insert(1) } />
			<DropZoneCell name="DF2" enabled={$dfConnected[2]} on:drive={ () => insert(2) } />
			<DropZoneCell name="DF3" enabled={$dfConnected[3]} on:drive={ () => insert(3) } />
	</div>
</div>
