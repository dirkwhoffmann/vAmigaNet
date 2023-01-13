<script lang="ts">
	import '../app.css';
	import { onMount } from 'svelte';
	import ButtonLink from '$lib/ButtonLink.svelte';
	import Icon from '$lib/Icon.svelte';
	import MainPageLink from '$lib/HeroLink.svelte';
	import FaGithub from 'svelte-icons/fa/FaGithub.svelte';
	import GoGear from 'svelte-icons/go/GoGear.svelte';
	import DiGrails from 'svelte-icons/di/DiGrails.svelte';
	import '@splidejs/svelte-splide/css';

	onMount(() => {
		console.log('onMount');
	});
</script>

<body class="h-screen bg-black text-white">
	<div class="bg-cover bg-transparent">
		<title>vAmiga Online</title>

		<div class="flex flex-col h-screen">
			<div
				class="absolute flex flex-grow bg-splashscreen bg-cover h-screen w-screen blur brightness-[0.9]"
			/>
			<div
				class="relative bg-transparent flex flex-grow items-center justify-center border-none align-middle border-4 border-blue-500"
			>
				<div class="rounded flex justify-center w-1/2">
					<div class="border-none border-4 p-4">
						<img class="h-24" src="va-icon.png" />
					</div>
					<div class="border-none border-4 p-4">
						<div class="flex">
							<div class="font-sofia-extra text-7xl mr-2">vAmiga</div>
							<!-- <div class="font-sofia-extra text-6xl mr-2">::</div>-->
							<div class="font-sofia-extra text-7xl  text-gray-300">Online</div>
						</div>
						<div class="font-sofia-semi text-xl text-gray-300 pl-2 pb-10">Version 0.1</div>
						<div class="flex space-x-5">
							<button
								class="bg-blue-300 hover:bg-blue-500 text-gray-800 font-sofia-semi text-xl py-2 px-8 rounded-md"
								>Power On</button
							>
							<button
								class="bg-blue-300 hover:bg-blue-500 text-gray-800 font-sofia-semi text-xl py-2 px-2 rounded-md"
								><Icon><FaGithub /></Icon></button
							>
						</div>
					</div>
				</div>
			</div>
			<div
				class="relative flex justify-center border-none align-middle bg-gray-900/50 space-x-8 border-4 border-red-500"
			>
				<MainPageLink href="#configure">
					<div slot="icon"><GoGear /></div>
					<div slot="description">Configure</div>
				</MainPageLink>
				<MainPageLink href="/showcases">
					<div slot="icon"><DiGrails /></div>
					<div slot="description">Showcase</div>
				</MainPageLink>
			</div>
		</div>
	</div>
</body>
