<!--
<svelte:window on:error|capture={e => handleError(e.error)}
               on:unhandledrejection|capture={e => handleError(e.reason)} />
-->
<script lang="ts">
	import '../app.css';
	import { proxy, amiga, poweredOn, what, errno } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import '@splidejs/svelte-splide/css';
	import Sidebar from '$lib/sidebar/Sidebar.svelte';
	import TitleScreen from '$lib/TitleScreen.svelte';

	let mounted = false;
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
		event.preventDefault();
			$what = $amiga.what();
			$errno = $amiga.errorCode();
			console.log('Unhandled error catched');
	}

	function sidebarAction(event) {
		console.log('Sidebar: ' + event.detail.sender);
	}
</script>

<body class="h-screen bg-black text-white scroll-smooth overflow-y-scroll">
	<title>vAmiga Online</title>
	<div id="top" transition:fade class="bg-cover bg-transparent">
		<TitleScreen show={mounted} />
	</div>
	<Sidebar on:select={sidebarAction} />
</body>
