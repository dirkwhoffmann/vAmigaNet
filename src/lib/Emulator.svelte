<svelte:options accessors={true} />

<script lang="ts">
	import { onMount } from 'svelte';
	import { layout, amiga, poweredOn } from '$lib/stores';
	import { canvasWidth, canvasHeight, aspectWidth, aspectHeight } from '$lib/stores';
	import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import { AnimatedFloat } from '$lib/utils/AnimatedFloat';
	import { TextureRect } from '$lib/utils/TextureRect';
	import { fade } from 'svelte/transition';

	// Component references
	let glCanvas: GLCanvas;

	// Texture cutout
	let x1 = 0;
	let y1 = 0;
	let x2 = 0;
	let y2 = 0;

	// Visible texture area
	export let textureRect = new TextureRect();

	// Size of the emulator canvas
	let recw = new AnimatedFloat(0);
	let rech = new AnimatedFloat(0);

	// Triggers for redrawing the emulator canvas
	let w = 0;
	let h = 0;

	// Indicates if the emulator canvas is animating
	let animating = false;

	$: canvasBorder = animating ? 'border-2 border-gray-600' : '';

	onMount(() => {
		console.log('Emulator: onMount()');
		// glCanvas.enableDrawing = true;
		textureRect.zoomIn();

		// window.requestAnimationFrame(doAnimationFrame);
	});

	$: updateRect($layout);

	export function updateRect(layout: string) {
		console.log('updateRect(', layout, ')');
		if (layout == 'full') {
			recw.set($canvasWidth);
			rech.set($canvasHeight);
		} else if (layout == 'aspect') {
			recw.set($aspectWidth);
			rech.set($aspectHeight);
		} else if (layout == 'fit') {
			const x1 = textureRect.x1.current * textureRect.texW;
			const y1 = textureRect.y1.current * textureRect.texH;
			const x2 = textureRect.x2.current * textureRect.texW;
			const y2 = textureRect.y2.current * textureRect.texH;
			recw.set(x2 - x1 + 2);
			rech.set(2 * (y2 - y1 + 2));
		}
	}

	export function doAnimationFrame(animationFrame: number, now: DOMHighResTimeStamp) {

		if (animationFrame % 50 == 0) {
			console.log(":: Frame " + animationFrame);
			if (!glCanvas) console.log("NO GLCANVAS");
		}

		if ($poweredOn) {
			update(now);
			render();
		} else {
			// console.log('Skipping draw: Store not yet initialized');
		}
	}

	function update(now: DOMHighResTimeStamp) {
		let textureAnimates = textureRect.animates();
		let canvasAnimates = recw.animates() || rech.animates();
		animating = textureAnimates || canvasAnimates;

		if (textureAnimates) {
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

			// In 1:1 mode, use the new texture size as the emulator canvas size to get a smooth effect
			if ($layout == 'fit') {
				w = recw.current = recw.target = x2 - x1 + 2;
				h = rech.current = rech.target = 2 * (y2 - y1 + 2);
			}
		}
		if (canvasAnimates) {
			recw.move();
			rech.move();
			w = recw.current;
			h = rech.current;
		}

		glCanvas.update(now);
	}

	function render() {
		glCanvas.render();
	}
</script>

{#if $poweredOn}
	<div class="relative grow h-full flex flex-col justify-center" transition:fade>
		<div class="flex justify-center h-full items-center">
			<div class="{canvasBorder}" style="height:{h}px; width:{w}px">
				<GLCanvas bind:this={glCanvas} />
			</div>
		</div>
	</div>
{/if}
