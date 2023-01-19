<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import Button from '$lib/widgets/Button.svelte';
	import { vAmiga } from '$lib/stores';
	import { goto } from '$app/navigation';
	import RetroShell from '$lib/RetroShell.svelte';
	import DiTerminal from 'svelte-icons/di/DiTerminal.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	let showShell = true;

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
</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="h-screen flex flex-col">
		<div>
			<div class="z-30 w-screen bg-white/30 flex space-x-2 p-2">
				<Button on:click={goBack} label="Back"><FaAngleLeft /></Button>
				<Button on:click={openShell}><DiTerminal /></Button>
			</div>
		</div>
		{#if showShell}
		<div class="border-none border-red-500 flex-grow overflow-scroll">
			<RetroShell />
		</div>
		{/if}
	</div>
</body>
