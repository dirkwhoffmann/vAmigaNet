<script lang="ts">

	import { onMount } from 'svelte';
	import { vAmiga } from '$lib/stores';
	import Emscripten from '$lib/Emscripten.svelte';

	let loadWasm = false;
	let emscripten: Emscripten; 

	onMount(() => {
		
		$vAmiga.onRuntimeInitialized = () => {
			console.log('onRuntimeInitialized');
			emscripten.createProxies();
		};

		// Bind to emscripten 
		window.Module = $vAmiga;

		// Source in vAmiga.js 
		loadWasm = true;
	});

</script>

<svelte:head>
	{#if loadWasm}
		<script>
			console.log('Loading vAmiga.js');
		</script>
		<script src="vAmiga.js"></script>
		<Emscripten bind:this={emscripten} />
	{/if}
</svelte:head>
<slot />
