<script lang="ts">

	import { onMount } from 'svelte';
	import { vAmiga } from '$lib/stores';
	import Emscripten from '$lib/Emscripten.svelte';
// 	import { Helper } from '../module.js';

	let loadWasm = false;
	
	onMount(() => {
		
		/*
		$vAmiga.onRuntimeInitialized = () => {
			console.log('onRuntimeInitialized');
			$ems.onRuntimeInitialized();
		};
		*/

		// Bind to emscripten 
		window.Module = $vAmiga;
 
		// Source in vAmiga.js 
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
