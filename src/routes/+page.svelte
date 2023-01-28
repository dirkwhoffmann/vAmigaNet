<script lang="ts">
	import '../app.css';
	import { proxy, amiga } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import { demos } from './showcases/database';
	import Button from '$lib/widgets/Button.svelte';
	import MainPageLink from '$lib/widgets/MainPageLink.svelte';
	import FaGithub from 'svelte-icons/fa/FaGithub.svelte';
	import GoGear from 'svelte-icons/go/GoGear.svelte';
	import DiGrails from 'svelte-icons/di/DiGrails.svelte';
	import FaInfoCircle from 'svelte-icons/fa/FaInfoCircle.svelte';
	import '@splidejs/svelte-splide/css';
	import { poweredOn } from '$lib/stores';

	let show = false;
	let guru = true;
	setInterval(() => {
		guru = !guru;
	}, 800);
	$: borderColor = guru ? 'border-red-800' : 'border-transparent';

	let buttonText = 'Run Demo';

	onMount(() => {
		console.log('+page: onMount()');
		buttonText = $poweredOn ? "Continue" : "Run Demo";
		show = true;
	});

	function understood() {
		console.log('understood()');
		goto('#top');
	}

	async function powerOn() {
		// await $proxy.setupAudio();
		goto('/emulator');
	}

	async function runDemo() {
		if (!$poweredOn) {
			await $proxy.runShowcase(demos[0]);
		}
		goto('/emulator');
	}

	function openShowcases() {
		goto('/showcases');
	}

	function gotoGitHub() {
		goto('https://dirkwhoffmann.github.io/vAmiga');
	}
</script>

<body class="h-screen bg-black text-white scroll-smooth overflow-y-scroll">
	<title>vAmiga Online</title>

	<div id="top" transition:fade class="bg-cover bg-transparent">
		<div class="flex flex-col h-screen">
			{#key show}
				<div
					in:fade={{ duration: 1000 }}
					class="absolute flex flex-grow bg-splashscreen bg-cover h-screen w-screen blur brightness-[0.9]"
				/>
				<div
					in:fade
					class="relative bg-transparent flex flex-grow items-center justify-center border-none align-middle border-4 border-blue-500"
				>
					<div class="rounded flex justify-center w-1/2">
						<div class="border-none border-4 p-4">
							<img class="h-24" src="va-icon.png" alt="vAmiga Icon" />
						</div>
						<div class="border-none border-4 p-4">
							<div class="flex">
								<div class="font-sofia-extra text-7xl mr-2">vAmiga</div>
								<div class="font-sofia-extra text-7xl  text-gray-300">Online</div>
							</div>
							<div class="font-sofia-semi text-xl text-gray-300 pl-2 pb-10">Version 0.1</div>
							<div class="flex space-x-5">
								<!--<Button on:click={powerOn} label="Power On" />-->
								<Button on:click={runDemo} label="{buttonText}" />
								<Button on:click={gotoGitHub}><FaGithub /></Button>
							</div>
						</div>
					</div>
				</div>
			{/key}
			<div
				class="relative flex justify-center border-none align-middle bg-gray-900/50 space-x-8 border-4 border-red-500"
			>
				<MainPageLink href="#configure">
					<div slot="icon"><GoGear /></div>
					<div slot="description">Configure</div>
				</MainPageLink>
				<!--
				<MainPageLink href="#about">
					<div slot="icon"><FaInfoCircle /></div>
					<div slot="description">Learn more</div>
				</MainPageLink>
				-->
				<MainPageLink href="/showcases">
					<div slot="icon"><DiGrails /></div>
					<div slot="description">Showcase</div>
				</MainPageLink>
			</div>
		</div>
		<div
			id="configure"
			class="relative border-[20px] {borderColor} h-96 flex justify-center bg-gray-900/50"
		>
			<div
				class="h-full w-2/3 border-none flex flex-col justify-center text-2xl font-josefin text-center"
			>
				<p class="">
					This page is under construction and offers very little functionality, yet. I.e., it is
					only possible to launch vAmiga with a number of preset demos. You'll find a suitable
					selection in the Showcases section. The site is intended as a feature preview to gather
					feedback from the user base. Based on the feedback I will decide to continue the project
					or to shut it down.
				</p>
				<div class="flex justify-center mt-10">
					<Button on:click={understood} label="Understood" />
				</div>
			</div>
		</div>
	</div>
</body>
