<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import { vAmiga, amiga } from '$lib/stores';
	import { TextureRect } from '$lib/utils/TextureRect';
	import Button from '$lib/widgets/Button.svelte';
	import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	import { text } from 'svelte/internal';

	// Component references
	let glCanvas: GLCanvas;

	// Indicates if RetroShell should be displayed
	let showShell = false;

	// The currently visible area
	let textureRect = new TextureRect();

	onMount(() => {
		console.log('onMount()');
		glCanvas.enableDrawing = true;

		window.requestAnimationFrame(doAnimationFrame);
	});

	function doAnimationFrame(now: DOMHighResTimeStamp) {
		if ($amiga != undefined) {
			update(now);
			render();
		} else {
			console.log('Skipping draw: Store not yet initialized');
		}
		window.requestAnimationFrame(doAnimationFrame);
	}

	function update(now: DOMHighResTimeStamp) {
		if (textureRect.animates()) {
			textureRect.move();
			glCanvas.updateTextureRect(
				textureRect.x1.current,
				textureRect.y1.current,
				textureRect.x2.current,
				textureRect.y2.current
			);
		}

		glCanvas.update(now);
	}

	function render() {
		glCanvas.render();
	}

	function goBack() {
		console.log('goBack()');
		goto('/');
	}
	function openShell() {
		console.log('openShell()');
		showShell = !showShell;
	}

	function openMonitor() {
		console.log('openMonitor()');
		if (textureRect.x2.target == 1.0) {
			textureRect.zoomIn();
			$amiga.configure($vAmiga.OPT_DMA_DEBUG_ENABLE, 0);
		} else {
			textureRect.zoomOut();
			$amiga.configure($vAmiga.OPT_DMA_DEBUG_ENABLE, 1);
		}
	}

	let clipped_width = 912;
	let clipped_height = 313;
</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="h-screen flex flex-col">
		<div>
			<div class="z-30 w-screen bg-white/30 flex space-x-2 p-2">
				<Button on:click={goBack}><FaAngleLeft /></Button>
				<Button on:click={openShell} img="retroShellIcon.png" />
				<Button on:click={openMonitor} img="monitorIcon.png" />
			</div>
		</div>
		<!-- <div class="relative w-full h-full"> -->
		<div class="relative w-[912px] h-[626px]">
			<GLCanvas bind:this={glCanvas} />
			{#if showShell}
				<div
					transition:fade
					class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll"
				>
					<RetroShell />
				</div>
			{/if}
		</div>
	</div>
</body>
