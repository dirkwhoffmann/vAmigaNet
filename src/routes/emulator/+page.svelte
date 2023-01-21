<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import Button from '$lib/widgets/Button.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	import { vAmiga } from '$lib/stores';
	let showShell = false;
	let canvas:HTMLCanvasElement;
	let ctx:CanvasRenderingContext2D;
	onMount(() => {
		console.log('onMount()');
		ctx = canvas.getContext('2d');
		if(ctx)
		{
			//if we get the context start rendering every VSync
			requestAnimationFrame(do_animation_frame);
		}

	});

	function goBack() {
		console.log('goBack()');
		goto('/');
	}
	function openShell() {
		console.log('openShell()');
		showShell = !showShell;
	}
	
	let clipped_width=725;
	let clipped_height=568;


	function draw(now){
		let pixels = $vAmiga.pixelBuffer();
	
		let image_data=ctx.createImageData(clipped_width,clipped_height);
		image_data.data.set(pixels, 0);
		ctx.putImageData(image_data,0,0); 
	}

	let stop_request_animation_frame=false;
	function do_animation_frame(now) {
		draw(now);
		if(!stop_request_animation_frame)
		{
			requestAnimationFrame(do_animation_frame);   
		}
	}


</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="h-screen flex flex-col">
		<div>
			<div class="z-30 w-screen bg-white/30 flex space-x-2 p-2">
				<Button on:click={goBack}><FaAngleLeft /></Button>
				<Button on:click={openShell} img="retroShellIcon.png"></Button>
			</div>
		</div>
		<div class="relative w-full h-full">
			<canvas bind:this={canvas} class="" width="724" height="568" tabindex="-1"></canvas>
			{#if showShell}
				<div transition:fade class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll">
					<RetroShell />
				</div>
			{/if}
		</div>
	</div>
</body>
