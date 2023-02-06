<script lang="ts">
	import '../app.css';
	import { initialized, proxy, amiga } from '$lib/stores';
	import { poweredOn, what, errno } from '$lib/stores';
	import { layout, showSidebar, showShell, showSettings } from '$lib/stores';
	import { canvasWidth, canvasHeight } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import '@splidejs/svelte-splide/css';
	import Sidebar from '$lib/sidebar/Sidebar.svelte';
	import TitleScreen from '$lib/TitleScreen.svelte';
	import DragAndDrop from '$lib/DragAndDrop.svelte';
	import Emulator from '$lib/Emulator.svelte';
	import Settings from '$lib/settings/Settings.svelte';
	import StatusBar from '$lib/StatusBar.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import MainScreen from '$lib/MainScreen.svelte';
	import type { AnyNode } from 'postcss';

	let mounted = false;
	let buttonText = 'Run Demo';

	// Component references
	let emulator: Emulator;
	let canvas: Element;

	$: if (canvas != undefined) {

		const resizeObserver = new ResizeObserver((entries) => {
			const entry = entries.at(0);
			$canvasWidth = entry!.contentRect.width;
			$canvasHeight = entry!.contentRect.height;
		});

		console.log('Creating resizeObserver...');
		resizeObserver.observe(canvas);
	}

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
				$showShell = !$showShell;
				if ($showShell) $showSettings = false;
				break;
			case 'settings':
				$showSettings = !$showSettings;
				if ($showSettings) $showShell = false;
				break;
			case 'monitor':
				if ($amiga.getConfig($proxy.OPT_DMA_DEBUG_ENABLE)) {
					emulator.textureRect.zoomIn();
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 0);
				} else {
					emulator.textureRect.zoomOut();
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
			case 'fit':
				$layout = 'fit';
				break;
			case 'aspect':
				$layout = 'aspect';
				break;
			case 'full':
				$layout = 'full';
				break;
			default:
				console.log('Unhandled sender: ' + sender);
		}
	}

	function push(event: Event) {
		const sender = event.detail.sender;
		console.log('Status bar: ', sender);

		$showSidebar = !$showSidebar;
	}
</script>

<body class="h-screen bg-black text-white scroll-smooth overflow-y-scroll">
	<title>vAmiga Online</title>
	<MainScreen>
		<StatusBar on:push={push} />
		<div bind:this={canvas} class="box relative grow border-2 border-green-300">
			{#if !$poweredOn}
				<TitleScreen />
			{/if}
			<Emulator bind:this={emulator} />
			{#if $showShell}
				<RetroShell />
			{/if}
			{#if $showSettings}
				<Settings />
			{/if}
			{#if $showSidebar}
				<Sidebar on:select={sidebarAction} />
			{/if}
		</div>
	</MainScreen>
</body>
