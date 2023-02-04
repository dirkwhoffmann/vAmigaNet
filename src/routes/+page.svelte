<!--
<svelte:window on:error|capture={e => handleError(e.error)}
               on:unhandledrejection|capture={e => handleError(e.reason)} />
-->
<script lang="ts">
	import '../app.css';
	import { initialized, proxy, amiga, poweredOn, what, errno } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import '@splidejs/svelte-splide/css';
	import Sidebar from '$lib/sidebar/Sidebar.svelte';
	import TitleScreen from '$lib/TitleScreen.svelte';
	import DragAndDrop from './emulator/DragAndDrop.svelte';
	import Emulator from '$lib/Emulator.svelte';
	import Settings from '$lib/settings/Settings.svelte';
	import RetroShell from '$lib/RetroShell.svelte';

	let mounted = false;
	let showSettings = false;
	let showShell = false;
	let buttonText = 'Run Demo';

	// Component references
	let emulator: Emulator;

	onMount(() => {
		console.log('+page: onMount()');
		buttonText = $poweredOn ? 'Continue' : 'Run Demo';
		mounted = true;

		window.addEventListener('error', handleUncatchedError);
		window.addEventListener('unhandledrejection', handleUncatchedError);
	});

	function handleUncatchedError(event) {
		console.log('Unhandled error catched', event);
		event.preventDefault();
		$what = $amiga.what();
		$errno = $amiga.errorCode();
	}

	function sidebarAction(event) {

		const sender = event.detail.sender; 

		console.log('Sidebar: ', sender);

		switch (event.detail.sender) {

			case 'shell':
				showShell = !showShell;
				break;
			case 'settings':
				showSettings = !showSettings;
				break;
			case 'monitor':
				if ($amiga.getConfig($proxy.OPT_DMA_DEBUG_ENABLE)) {
					console.log("Callig zoom in");
					emulator.textureRect.zoomIn();
					console.log("Exiting DMA debugger");
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 0);
				} else {
					console.log("Callig zoom out");
					emulator.textureRect.zoomOut();
					console.log("Entering DMA debugger");
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 1);
				}
				break;
			case 'pause':
				$amiga.stopAndGo();
				break;
			case 'power':
				if ($amiga.poweredOn()) {
					$amiga.powerOff();
				} else {
					$amiga.run();
				}
				break;
			case 'reset':
				$amiga.hardReset();
				break;
			default:
				console.log('Unhandled sender: ' + sender);
		}
	}
</script>

<body class="h-screen bg-black text-white scroll-smooth overflow-y-scroll">
	<title>vAmiga Online</title>
	<DragAndDrop>
		{#if $initialized}
			{#if !$poweredOn}
				<div id="top" transition:fade class="bg-cover bg-transparent">
					<TitleScreen show={mounted} />
				</div>
			{:else}
				<div transition:fade class="bg-cover bg-transparent">
					<Emulator bind:this={emulator} show={mounted} />
				</div>
			{/if}
			<Sidebar on:select={sidebarAction} />

			{#if showSettings}
				<div
					transition:fade
					class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll"
				>
					<Settings />
				</div>
			{/if}

			{#if showShell}
				<div
					transition:fade
					class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll"
				>
					<RetroShell />
				</div>
			{/if}
		{/if}
	</DragAndDrop>
</body>
