<svelte:options accessors={true}/>

<script lang="ts">
	import { onMount } from 'svelte';
    import { amiga } from '$lib/stores';
    import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import { TextureRect } from '$lib/utils/TextureRect';
    import { fade } from 'svelte/transition';

	// Component references
	let glCanvas: GLCanvas;

    let w = 0;
	let h = 0;

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
        let x1 = textureRect.x1.current * textureRect.texW;
        let y1 = textureRect.y1.current * textureRect.texH;
        let x2 = textureRect.x2.current * textureRect.texW;
        let y2 = textureRect.y2.current * textureRect.texH;
        w = x2 - x1 + 2;
        h = y2 - y1 + 2;
    }

    glCanvas.update(now);
}

function render() {
    glCanvas.render();
}

</script>

<div class="relative grow h-full flex flex-col justify-center" transition:fade>
	<div class="flex justify-center">
		<div class="border-2 border-gray-600" style="height:{2 * h}px; width:{w}px">
			<GLCanvas bind:this={glCanvas} />
		</div>
	</div>
</div>
