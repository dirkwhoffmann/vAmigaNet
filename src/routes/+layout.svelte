<script lang="ts">
	import { onMount } from 'svelte';
	import { audio, config, proxy } from '$lib/stores';
	import Audio from '$lib/Globals/Audio.svelte';
	import Config from '$lib/Globals/Config.svelte';
	import Guru from '$lib/Guru.svelte';
	import Proxy from '$lib/Proxy.svelte';

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
	<Config bind:this={$config} />

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
