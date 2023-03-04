<script lang="ts">
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import DiGrails from 'svelte-icons/di/DiGrails.svelte';
	import FaGithub from 'svelte-icons/fa/FaGithub.svelte';
	import FaMicrochip from 'svelte-icons/fa/FaMicrochip.svelte';
	import GoLaw from 'svelte-icons/go/GoLaw.svelte';
	import { Layer } from '$lib/types';
	import MainPageLink from '$lib/Widgets/MainPageLink.svelte';
	import Impressum from '$lib/Impressum.svelte';
	import RomViewer from '$lib/RomViewer.svelte';
	import Showcases from '$lib/Showcases/Showcases.svelte';
	import { audio, amiga, layer, showSidebar } from '$lib/stores';

	let debug = ''; // 'border-2';
	let showRomViewer = false;
	let showImpressum = false;

	$: if (($layer == Layer.kickstart)) {
		console.log('Layer.kickstart...');
		showRomViewer = true;
	}

	async function launch() {
		await $audio.setup();
		$amiga.run();
	}

	function gotoGitHub() {
		goto('https://dirkwhoffmann.github.io/vAmiga');
	}

	/*
	function setTheme(theme: string) {
		document.querySelector('html')?.setAttribute('data-theme', theme);
	}
	*/

	async function openShowcases() {
		await $audio.setup();
		$layer = $layer == Layer.showcases ? Layer.none : Layer.showcases;
		$showSidebar = false;
	}

	async function openRoms() {
		await $audio.setup();
		showRomViewer = true;
	}

	function openImpressum() {
		showImpressum = true;
	}
</script>

<div class="modal" class:modal-open={showRomViewer}>
	<div class="modal-box h-2/3 w-2/3 max-w-none">
		<RomViewer bind:show={showRomViewer} />
	</div>
</div>

<div class="modal" class:modal-open={showImpressum}>
	<div class="modal-box">
		<Impressum bind:show={showImpressum} />
	</div>
</div>

<div class="h-full flex flex-col {debug}" transition:fade>
	<div in:fade={{ duration: 2000 }}>
		<!--<div class="absolute w-full h-full bg-base-100" />-->
		<div class="absolute h-full blur-sm">
			<div class="h-full w-screen bg-gradient-to-t from-primary to-secondary" />
		</div>
		<div class="absolute h-full blur-sm">
			<img class="h-full w-screen object-fill opacity-60" src="matrix.jpg" alt="Background" />
		</div>
	</div>
	{#if $layer == Layer.showcases}
		<Showcases />
	{:else}
		<div
			in:fade
			class="relative bg-transparent grow flex flex-col items-center justify-center {debug}"
		>
		{#if $layer == Layer.none}
			<div class={debug}>
				<div class="rounded flex justify-center">
					<img class="h-24 p-2 mt-3" src="va-icon.png" alt="vAmiga Icon" />
					<div class="p-6 text-white">
						<div class="flex">
							<div class="font-sofia-extra text-7xl mr-2">vAmiga</div>
							<div class="font-sofia-extra text-7xl opacity-75">Online</div>
						</div>
						<div class="font-sofia-semi text-xl pl-2 pb-10">Version 0.2</div>
						<div class="flex space-x-5">
							<button class="btn btn-primary" on:click={launch}>Power On</button>
							<button class="btn btn-primary btn-square p-1.5" on:click={gotoGitHub}><FaGithub /></button>
						</div>
					</div>
				</div>
			</div>
			{/if}
		</div>
	{/if}
	<div class="relative flex justify-center align-middle bg-gray-900/50 space-x-8 {debug}">
		<!--
			<MainPageLink href="#learnmore">
				<div slot="icon"><FaBookOpen /></div>
				<div slot="description">Learn more</div>
			</MainPageLink>
            -->
		<MainPageLink on:click={openRoms}>
			<div slot="icon" class="p-1.5"><FaMicrochip /></div>
			<div slot="description">Kickstart</div>
		</MainPageLink>
		<MainPageLink on:click={openShowcases}>
			<div slot="icon"><DiGrails /></div>
			<div slot="description">Showcases</div>
		</MainPageLink>
		<MainPageLink on:click={openImpressum}>
			<div slot="icon"><GoLaw /></div>
			<div slot="description">Impressum</div>
		</MainPageLink>
	</div>
</div>
