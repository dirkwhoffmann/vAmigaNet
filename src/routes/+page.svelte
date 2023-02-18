<script lang="ts">
	import '../app.css';
	import { initialized, proxy, amiga } from '$lib/stores';
	import { poweredOn, what, errno } from '$lib/stores';
	import { layout, showSidebar, showShell, showSettings, showImpressum } from '$lib/stores';
	import { canvasWidth, canvasHeight, aspectWidth, aspectHeight } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import '@splidejs/svelte-splide/css';
	import Sidebar from '$lib/sidebar/Sidebar.svelte';
	import TitleScreen from '$lib/TitleScreen.svelte';
	import Emulator from '$lib/Emulator.svelte';
	import Settings from '$lib/settings/Settings.svelte';
	import StatusBar from '$lib/statusbar/StatusBar.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import MainScreen from '$lib/MainScreen.svelte';
	import Impressum from '$lib/Impressum.svelte';
	import BrowserCheck from '$lib/BrowserCheck.svelte';

	let mounted = false;
	let buttonText = 'Run Demo';

	// Animation frame counter
	let animationFrame = 0;

	// Component references
	let emulator: Emulator;
	let canvas: Element;
	let statusBar: StatusBar;

	// Timeout for debouncing the resize event
	let timeout: NodeJS.Timeout;

	onMount(() => {
		console.log('+page: onMount()');
		buttonText = $poweredOn ? 'Continue' : 'Run Demo';
		mounted = true;

		window.addEventListener('resize', function () {
			clearTimeout(timeout);
			timeout = setTimeout(handleResizeEvent, 250);
		});

		window.addEventListener('error', handleUncatchedError);
		window.addEventListener('unhandledrejection', handleUncatchedError);
	});

	$: if (canvas != undefined) resize();

	$: if ($initialized) {
		// Start render loop
		window.requestAnimationFrame(doAnimationFrame);
	}

	function doAnimationFrame(now: DOMHighResTimeStamp) {
		animationFrame++;

		if (emulator) {
			emulator.doAnimationFrame(animationFrame, now);
		}
		if (statusBar) {
			statusBar.update(animationFrame, now);
		}

		window.requestAnimationFrame(doAnimationFrame);
	}

	function resize() {
		if (canvas != undefined) {
			// Copy the current size of emulator element
			$canvasWidth = canvas.clientWidth;
			$canvasHeight = canvas.clientHeight;

			// Compute the biggest possible 4:3 box
			$aspectWidth = $canvasWidth;
			$aspectHeight = ($aspectWidth * 3) / 4;
			if ($aspectHeight > $canvasHeight) {
				$aspectHeight = $canvasHeight;
				$aspectWidth = ($aspectHeight * 4) / 3;
			}

			emulator.updateRect($layout);
			console.log('dimensions: ', $canvasWidth, ', ', $canvasHeight);
			console.log('aspect dimensions: ', $aspectWidth, ', ', $aspectHeight);
		}
	}

	function handleResizeEvent() {
		resize();
	}

	function handleUncatchedError(event: Event) {
		if (event.reason instanceof WebAssembly.Exception) {
			// event.preventDefault();
			$what = $amiga.what();
			$errno = $amiga.errorCode();
		}
	}

	function sidebarAction(event: CustomEvent<{ sender: string; state: boolean }>) {
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
					emulator.textureRect!.zoomIn();
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 0);
				} else {
					emulator.textureRect!.zoomOut();
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 1);
				}
				break;
			case 'pause':
				try {
					$amiga.stopAndGo();
				} catch (exc) {
					console.log(exc);
					$proxy.reportException();
				}
				break;
			case 'power':
				try {
					if ($amiga.poweredOn()) {
						$amiga.powerOff();
					} else {
						$amiga.run();
					}
				} catch (exc) {
					console.log(exc);
					$proxy.reportException();
				}
				break;
			case 'reset':
				try {
					$amiga.hardReset();
				} catch (exc) {
					console.log(exc);
					$proxy.reportException();
				}
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

	function push(event: CustomEvent<{ sender: string }>) {
		const sender = event.detail.sender;
		console.log('Status bar: ', sender);

		$showSidebar = !$showSidebar;

		if (!$showSidebar) {
			$showSettings = false;
			$showShell = false;
		}
	}
</script>

<body>
	<div class="h-screen bg-black text-white scroll-smooth overflow-y-auto">
		<title>vAmiga Online</title>
		<MainScreen>
			<StatusBar bind:this={statusBar} on:push={push} />
			<div bind:this={canvas} class="box relative grow border-none border-green-300 overflow-auto">
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
			<BrowserCheck />
			{#if $showImpressum}
				<Impressum />
			{/if}
		</MainScreen>
	</div>
</body>
