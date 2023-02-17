<script lang="ts">
	import { onMount } from 'svelte';
	import { proxy, audio } from '$lib/stores';
	import Proxy from '$lib/Proxy.svelte';
	import Audio from '$lib/Audio.svelte';
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
	<Audio bind:this={$audio} />
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
