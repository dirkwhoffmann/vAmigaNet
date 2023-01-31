<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import { proxy, amiga } from '$lib/stores';
	import { TextureRect } from '$lib/utils/TextureRect';
	import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	import Toolbar from '$lib/toolbar/Toolbar.svelte';
	import { MsgPause, running } from '$lib/stores';
	import DragAndDrop from './DragAndDrop.svelte';
	import Logo from '$lib/widgets/Logo.svelte';

	// Component references
	let glCanvas: GLCanvas;
	let toolbar: Toolbar;

	let w = 0;
	let h = 0;

	// Indicates if RetroShell should be displayed
	let showShell = false;

	// The currently visible area
	let textureRect = new TextureRect();

	onMount(() => {
		console.log('onMount()');
		glCanvas.enableDrawing = true;
		textureRect.zoomIn();

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
			let x1 = textureRect.x1.current * textureRect.texW;
			let y1 = textureRect.y1.current * textureRect.texH;
			let x2 = textureRect.x2.current * textureRect.texW;
			let y2 = textureRect.y2.current * textureRect.texH;
			w = (x2 - x1) + 2;
			h = (y2 - y1) + 2;
			// console.log("New canvas size: " + x1 + ", " + y1 + ", " + x2 + ", " + y2);
			console.log('New canvas size: ' + w + ', ' + h);
		}

		glCanvas.update(now);
	}

	function render() {
		glCanvas.render();
	}

	//
	// Event handling
	//

	function buttonClicked(e: PointerEvent) {
		let button = e.currentTarget! as HTMLButtonElement;

		console.log('id = ' + button.id);

		switch (button.id) {
			case 'home':
				goto('/');
				break;
			case 'retroShell':
				showShell = !showShell;
				break;
			case 'monitor':
				if ($amiga.getConfig($proxy.OPT_DMA_DEBUG_ENABLE)) {
					textureRect.zoomIn();
					$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 0);
				} else {
					textureRect.zoomOut();
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
				console.log('Invalid id: ' + button.id);
		}
	}

	let m = { x: 0, y: 0 };

	function handleMousemove(event) {
		const threshold = 50;

		if (m.y >= threshold && event.clientY < threshold) {
			console.log('-> SHOW');
			toolbar.showToolbar();
		}
		if (m.y < threshold && event.clientY >= threshold) {
			console.log('-> HIDE');
			toolbar.hideToolbar();
		}
		m.x = event.clientX;
		m.y = event.clientY;
	}
</script>

<body class="h-screen bg-black text-white" on:mousemove={handleMousemove}>
	<title>vAmiga Online</title>

	<!--
	<div>
		The mouse position is {m.x} x {m.y}
	</div>
	-->
	<DragAndDrop>
		<div class="border-4 h-screen w-screen flex flex-col justify-center">
			<!-- Canvas -->
			<!--<div class="relative w-full h-full">-->
			<div class="flex justify-center">
				<div class="border-2 border-gray-600" style="height:{2 * h}px; width:{w}px">
					<GLCanvas bind:this={glCanvas} />
					<!-- Retro Shell -->
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
			<!-- Toolbar -->
			<div class="absolute top-0 left-0">
				<Toolbar bind:this={toolbar} on:click={buttonClicked} />
			</div>
		</div>
	</DragAndDrop>
	<Logo />
</body>
