<script lang="ts">
	import { proxy, amiga, retroShell, poweredOn } from '$lib/stores';
	import { onMount } from 'svelte';
	import { demos } from '$lib/database';
	import MyButton from '$lib/widgets/MyButton.svelte';
	import FaGithub from 'svelte-icons/fa/FaGithub.svelte';
	import MainPageLink from '$lib/widgets/MainPageLink.svelte';
	import DiGrails from 'svelte-icons/di/DiGrails.svelte';
	import GoLaw from 'svelte-icons/go/GoLaw.svelte';
	import FaBookOpen from 'svelte-icons/fa/FaBookOpen.svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';

    let debug = ''; // 'border-2';

	function runDemo() {
		runMe();
		$proxy.audioContext.resume();
	}
	async function runMe() {
		console.log('runMe');
		if (!$poweredOn) {
			await $proxy.runShowcase(demos[0]);
		}
		// goto('/emulator');
	}

	function gotoGitHub() {
		goto('https://dirkwhoffmann.github.io/vAmiga');
	}
</script>

<div class="h-full flex flex-col {debug}" transition:fade>
	<!-- bg-cover bg-transparent-->

	<div in:fade={{ duration: 2000 }} class="absolute h-full blur brightness-[0.9]">
		<img class="h-full w-screen object-fill" src="matrix1.jpg" alt="Background" />
	</div>

	<div
		in:fade
		class="relative bg-transparent grow flex flex-col items-center justify-center {debug}"
	>
		<div class="{debug}">
			<div class="rounded flex justify-center">
				<img class="h-24 p-2 mt-3" src="va-icon.png" alt="vAmiga Icon" />
				<div class="p-6">
					<div class="flex">
						<div class="font-sofia-extra text-7xl mr-2">vAmiga</div>
						<div class="font-sofia-extra text-7xl  text-gray-300">Online</div>
					</div>
					<div class="font-sofia-semi text-xl text-gray-300 pl-2 pb-10">Version 0.1</div>
					<div class="flex space-x-5">
						<MyButton on:click={runDemo} label="Run Demo" />
						<MyButton on:click={gotoGitHub}><FaGithub /></MyButton>
					</div>
				</div>
			</div>
		</div>
		<div class="relative {debug} w-3/4 mt-5">
			<p class="font-josefin text-base text-red-400 text-center">
				This page is under construction and offers very little functionality, yet. I.e., it is only
				possible to launch vAmiga with a number of preset demos. You'll find a suitable selection in
				the Showcases section. The site is intended as a feature preview to gather feedback from the
				user base. Based on the feedback I will decide to continue the project or to shut it down.
			</p>
		</div>
	</div>
	<div
		class="relative flex justify-center align-middle bg-gray-900/50 space-x-8 {debug}"
	>
		<!--
			<MainPageLink href="#learnmore">
				<div slot="icon"><FaBookOpen /></div>
				<div slot="description">Learn more</div>
			</MainPageLink>
            -->
		<MainPageLink href="showcases">
			<div slot="icon"><DiGrails /></div>
			<div slot="description">Showcases</div>
		</MainPageLink>
		<MainPageLink href="#about">
			<div slot="icon"><GoLaw /></div>
			<div slot="description">Impressum</div>
		</MainPageLink>
	</div>
</div>
<!-- 
<div
	id="learnmore"
	class="relative border-[20px] border-red-600 h-96 flex justify-center bg-gray-900/50"
>
	<div
		class="h-full w-2/3 border-none flex flex-col justify-center text-2xl font-josefin text-center"
	>
		<p class="">
			This page is under construction and offers very little functionality, yet. I.e., it is only
			possible to launch vAmiga with a number of preset demos. You'll find a suitable selection in
			the Showcases section. The site is intended as a feature preview to gather feedback from the
			user base. Based on the feedback I will decide to continue the project or to shut it down.
		</p>
	</div>
</div>
-->
