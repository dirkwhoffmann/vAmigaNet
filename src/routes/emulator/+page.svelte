<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import Button from '$lib/widgets/Button.svelte';
	import GLCanvas from '$lib/widgets/GLCanvas.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	
	let showShell = false;
	let glCanvas: GLCanvas;

	onMount(() => {
		console.log('onMount()');
		glCanvas.enableDrawing = true;
		
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
