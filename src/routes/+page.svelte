<!--
<svelte:window on:error|capture={e => handleError(e.error)}
               on:unhandledrejection|capture={e => handleError(e.reason)} />
-->
<script lang="ts">
	import '../app.css';
	import { initialized, proxy, amiga, poweredOn, what, errno } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import '@splidejs/svelte-splide/css';
	import Sidebar from '$lib/sidebar/Sidebar.svelte';
	import TitleScreen from '$lib/TitleScreen.svelte';
	import DragAndDrop from './emulator/DragAndDrop.svelte';
	import Emulator from '$lib/Emulator.svelte';
	import Settings from '$lib/settings/Settings.svelte';
	import RetroShell from '$lib/RetroShell.svelte';

	let mounted = false;
	let showSettings = false;
	let showShell = false;
	let buttonText = 'Run Demo';

	const log = document.querySelector('.event-log-contents');

	onMount(() => {
		console.log('+page: onMount()');
		buttonText = $poweredOn ? 'Continue' : 'Run Demo';
		mounted = true;

		window.addEventListener('error', handleUncatchedError);
		window.addEventListener('unhandledrejection', handleUncatchedError);
	});

	function handleUncatchedError(event) {
		console.log('Unhandled error catched');
		/*
		if ($amiga != undefined) {
			event.preventDefault();
			$what = $amiga.what();
			$errno = $amiga.errorCode();
		}
		*/
	}

	function sidebarAction(event) {
		console.log('Sidebar: ' + event.detail.sender);
	}
</script>

<body class="h-screen bg-black text-white scroll-smooth overflow-y-scroll">
	<title>vAmiga Online</title>
	<DragAndDrop>
		{#if $initialized}
			{#if !$poweredOn}
				<div id="top" transition:fade class="bg-cover bg-transparent">
					<TitleScreen show={mounted} />
				</div>
			{:else}
				<div transition:fade class="bg-cover bg-transparent">
					<Emulator show={mounted} />
				</div>
			{/if}
			<Sidebar on:select={sidebarAction} />

			{#if showSettings}
				<div
					transition:fade
					class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll"
				>
					<Settings />
				</div>
			{/if}

			{#if showShell}
				<div
					transition:fade
					class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll"
				>
					<RetroShell />
				</div>
			{/if}
		{/if}
	</DragAndDrop>
</body>
