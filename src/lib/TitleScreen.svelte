<script lang="ts">
	import { proxy, audio, amiga, retroShell, poweredOn, showImpressum } from '$lib/stores';
	import { onMount } from 'svelte';
	import { demos } from '$lib/database';
	import MyButton from '$lib/widgets/MyButton.svelte';
	import FaGithub from 'svelte-icons/fa/FaGithub.svelte';
	import MainPageLink from '$lib/widgets/MainPageLink.svelte';
	import DiGrails from 'svelte-icons/di/DiGrails.svelte';
	import GoLaw from 'svelte-icons/go/GoLaw.svelte';
	import DiDatabase from 'svelte-icons/di/DiDatabase.svelte';
	import FaMicrochip from 'svelte-icons/fa/FaMicrochip.svelte';
	import FaBookOpen from 'svelte-icons/fa/FaBookOpen.svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import RomViewer from '$lib/RomViewer.svelte';
	import Showcases from '$lib/Showcases.svelte';

	let debug = ''; // 'border-2';
	let showRomViewer = false;
	let showShowcases = false; 

	async function runDemo() {
		await $audio.setup();
		if (!$poweredOn) {
			await $proxy.runShowcase(demos[0]);
		}
	}

	function gotoGitHub() {
		goto('https://dirkwhoffmann.github.io/vAmiga');
	}

	function setTheme(theme: string) {
		document.querySelector('html')?.setAttribute('data-theme', theme);
	}

	async function openShowcases() {
		showShowcases = !showShowcases;
	}

	async function openRoms() {
		showRomViewer = true;
	}

	function openImpressum() {
		$showImpressum = true;
	}
</script>

<div class="modal" class:modal-open={showRomViewer}>
	<div class="modal-box">
		<RomViewer bind:show={showRomViewer} />
	</div>
</div>

<div class="h-full flex flex-col {debug}" transition:fade>
	<div in:fade={{ duration: 2000 }} class="absolute h-full blur brightness-[0.9]">
		<img class="h-full w-screen object-fill" src="matrix1.jpg" alt="Background" />
	</div>
	{#if showShowcases}
	<Showcases />
	{:else}
	<div
		in:fade
		class="relative bg-transparent grow flex flex-col items-center justify-center {debug}"
	>
		<div class={debug}>
			<div class="rounded flex justify-center">
				<img class="h-24 p-2 mt-3" src="va-icon.png" alt="vAmiga Icon" />
				<div class="p-6">
					<div class="flex">
						<div class="font-sofia-extra text-7xl mr-2">vAmiga</div>
						<div class="font-sofia-extra text-7xl  text-gray-300">Online</div>
					</div>
					<div class="font-sofia-semi text-xl text-gray-300 pl-2 pb-10">Version 0.1.2</div>
					<div class="flex space-x-5">
						<button class="btn btn-primary" on:click={runDemo}>Run Demo</button>
						<button class="btn btn-primary p-1.5" on:click={gotoGitHub}><FaGithub /></button>
					</div>
				</div>
			</div>
		</div>
		<div class="relative {debug} w-2/3 mt-5">
			<p class="font-josefin text-base text-error text-center">
				This page is under construction and offers very little functionality, yet. I.e., it is only
				possible to launch vAmiga with a number of preset demos. You'll find a suitable selection in
				the Showcases section. The site is intended as a feature preview to gather feedback from the
				user base.
			</p>
		</div>
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
