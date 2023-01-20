<script lang="ts">

	import { onMount } from 'svelte';
	import { vAmiga } from '$lib/stores';
	import Emscripten from '$lib/Emscripten.svelte';

	let loadWasm = false;
	
	onMount(() => {
		
		// Bind to emscripten 
		window.Module = $vAmiga;
 
		// Let the script source in vAmiga.js 
		loadWasm = true;
	});

</script>

<svelte:head>
	<Emscripten bind:this={$vAmiga} />
	{#if loadWasm}
		<script>
			console.log('Loading vAmiga.js');
		</script>
		<script src="vAmiga.js"></script>
	{/if}
</svelte:head>
<slot />
