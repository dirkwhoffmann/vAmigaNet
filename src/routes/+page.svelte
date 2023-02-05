<script lang="ts">
	import '../app.css';
	import { proxy, amiga, poweredOn, what, errno } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import '@splidejs/svelte-splide/css';
	import Sidebar from '$lib/sidebar/Sidebar.svelte';
	import TitleScreen from '$lib/TitleScreen.svelte';
	import DragAndDrop from './emulator/DragAndDrop.svelte';
	import Emulator from '$lib/Emulator.svelte';
	import Settings from '$lib/settings/Settings.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import MainScreen from '$lib/MainScreen.svelte';

	let mounted = false;
	let showSettings = false;
	let showShell = false;
	let showSidebar = false;
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
					console.log('Callig zoom in');
					emulator.textureRect.zoomIn();
					console.log('Exiting DMA debugger');
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 0);
				} else {
					console.log('Callig zoom out');
					emulator.textureRect.zoomOut();
					console.log('Entering DMA debugger');
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

	function toggleSidebar(e: Event) {
		e.preventDefault();
		showSidebar = !showSidebar;
	}
</script>

<body class="h-screen bg-black text-white scroll-smooth overflow-y-scroll">
	<title>vAmiga Online</title>
	<MainScreen>
		<div class="relative grow">
			{#if !$poweredOn}
				<TitleScreen />
			{/if}
			{#if $poweredOn}
				<Emulator bind:this={emulator} />
			{/if}
			{#if showShell}
				<RetroShell />
			{/if}
			{#if showSettings}
				<Settings />
			{/if}
			{#if showSidebar}
				<Sidebar on:select={sidebarAction} expanded={showSidebar} />
			{/if}
		</div>

		<!--
			{#if !$poweredOn}
				<div id="top" transition:fade><TitleScreen show={mounted} /></div>
			{:else}
				<div transition:fade>
					<Emulator bind:this={emulator} show={mounted} />
				</div>
			{/if}

			{#if showSettings}
				<div transition:fade><Settings /></div>
			{/if}
			{#if showShell}
				<div transition:fade><RetroShell /></div>
			{/if}
		-->
		<div class="relative flex h-6">
			<div class="flex w-14 bg-gradient-to-t from-gray-300 to-gray-400 justify-center">
				<button type="button" class="" id="sidebarButton" on:click={toggleSidebar}>
					<img class="h-6 border-0" src="icons/vamigaIcon.png" alt="vAmiga Icon" />
				</button>
			</div>
			<div class="ml-0.5 bg-gradient-to-t from-gray-300 to-gray-400 grow" />
		</div>
	</MainScreen>
</body>
