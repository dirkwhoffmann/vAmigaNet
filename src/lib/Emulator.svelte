<svelte:options accessors={true} />

<script lang="ts">
	import { onMount } from 'svelte';
	import { layout, amiga, poweredOn, canvasWidth, canvasHeight } from '$lib/stores';
	import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import { TextureRect } from '$lib/utils/TextureRect';
	import { fade } from 'svelte/transition';

	// Component references
	let glCanvas: GLCanvas;

	// Texture cutout
	let x1 = 0;
	let y1 = 0;
	let x2 = 0;
	let y2 = 0;

	// Display size
	$: w = $layout == 'full' ? $canvasWidth : $layout == 'aspect' ? (h * 4) / 3 : x2 - x1 + 2;
	$: h = $layout == 'full' ? $canvasHeight : $layout == 'aspect' ? $canvasHeight : 2 * (y2 - y1 + 2);

    $: console.log('Size: ', $canvasWidth, ' x ', $canvasHeight);
    $: console.log('wh: ', w, ' x ', h);

	// The currently visible area
	export let textureRect = new TextureRect();

	onMount(() => {
		console.log('Emulator: onMount()');
		// glCanvas.enableDrawing = true;
		textureRect.zoomIn();

		window.requestAnimationFrame(doAnimationFrame);
	});

	function doAnimationFrame(now: DOMHighResTimeStamp) {
		if (glCanvas != undefined) {
			update(now);
			render();
		} else {
			// console.log('Skipping draw: Store not yet initialized');
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
			x1 = textureRect.x1.current * textureRect.texW;
			y1 = textureRect.y1.current * textureRect.texH;
			x2 = textureRect.x2.current * textureRect.texW;
			y2 = textureRect.y2.current * textureRect.texH;
			// w = x2 - x1 + 2;
			// h = y2 - y1 + 2;
		}

		glCanvas.update(now);
	}

	function render() {
		glCanvas.render();
	}


</script>

{#if $poweredOn}
	<div class="relative grow h-full flex flex-col justify-center" transition:fade>
		<div class="flex justify-center h-full">
			<div class="border-2 border-gray-600" style="height:{h}px; width:{w}px">
				<GLCanvas bind:this={glCanvas} />
			</div>
			<!--
                {#if $layout == 'aspect'}
            <div class="border-2 border-red-600 {aspect}">
                <GLCanvas bind:this={glCanvas} />
            </div>
			{/if}
			{#if $layout == 'full'}
            <div class="border-2 border-red-600 {aspect}">
                <GLCanvas bind:this={glCanvas} />
            </div>
            -->
		</div>
	</div>
{/if}
