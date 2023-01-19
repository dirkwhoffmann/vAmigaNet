<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import Button from '$lib/widgets/Button.svelte';
	import { vAmiga } from '$lib/stores';
	import { goto } from '$app/navigation';
	import RetroShell from '$lib/RetroShell.svelte';

	let showMenu = false;

	onMount(() => {
		console.log('onMount()');
	});

	function goBack() {
		console.log('goBack()');
		goto('/');
	}
</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="h-screen flex flex-col">
		<div>
			<div class="z-30 w-screen bg-white/30 space-x-2 p-2">
				<Button on:click={goBack} label="Back" width="w-16" />
			</div>
		</div>
		<div class="border-none border-red-500 flex-grow overflow-scroll">
			<RetroShell />
		</div>
	</div>
</body>
