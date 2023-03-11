<script lang="ts">
	import { onMount } from 'svelte';
	import { audio, config, gamepadManager, proxy } from '$lib/stores';
	import Audio from '$lib/Globals/Audio.svelte';
	import Config from '$lib/Globals/Config.svelte';
	import GamepadManager from '$lib/Globals/GamepadManager.svelte';
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
	<Audio bind:this={$audio} />
	<Config bind:this={$config} />
	<GamepadManager bind:this={$gamepadManager} />
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
