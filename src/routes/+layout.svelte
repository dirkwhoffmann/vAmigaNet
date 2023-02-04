<script lang="ts">
	import { onMount } from 'svelte';
	import { proxy, what } from '$lib/stores';
	import Proxy from '$lib/Proxy.svelte';
	import Guru from '$lib/Guru.svelte';

	let loadWasm = false;

	onMount(() => {
		console.log('+layout: onMount()');

		// Bind to emscripten
		window.Module = $proxy;

		// Let the script source in vAmiga.js
		loadWasm = true;
	});
</script>

<svelte:head>
	<Proxy bind:this={$proxy} />
	{#if loadWasm}
		<script>
			console.log('Loading vAmiga.js');
		</script>
		<script src="vAmiga.js"></script>
	{/if}
</svelte:head>
<Guru />
<div class="relative">
<slot />
</div>
