<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import Button from '$lib/widgets/Button.svelte';
	import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	// import { vAmiga } from '$lib/stores';
	
	let showShell = false;

	onMount(() => {
		console.log('onMount()');
	});

	function goBack() {
		console.log('goBack()');
		goto('/');
	}
	function openShell() {
		console.log('openShell()');
		showShell = !showShell;
	}

	let clipped_width = 912;
	let clipped_height = 313;

	/*
	function draw(now) {
		let pixels = $vAmiga.pixelBuffer();

		let image_data = gl.createImageData(clipped_width, clipped_height);
		image_data.data.set(pixels, 0);
		gl.putImageData(image_data, 0, 0);
	}

	let stop_request_animation_frame = false;
	function do_animation_frame(now) {
		draw(now);
		if (!stop_request_animation_frame) {
			window.requestAnimationFrame(do_animation_frame);
		}
	}
	*/
</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="h-screen flex flex-col">
		<div>
			<div class="z-30 w-screen bg-white/30 flex space-x-2 p-2">
				<Button on:click={goBack}><FaAngleLeft /></Button>
				<Button on:click={openShell} img="retroShellIcon.png" />
			</div>
		</div>
		<div class="relative w-full h-full">
			<GLCanvas />
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
