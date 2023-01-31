<script lang="ts">
	import '../../app.css';
	import { goto } from '$app/navigation';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import Carousel from '$lib/Carousel.svelte';
	import Button from '$lib/widgets/Button.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	import '@splidejs/svelte-splide/css';
	import { demos, games, tools } from './database';
	import { amiga, proxy } from '$lib/stores';
	import Logo from '$lib/widgets/Logo.svelte';

	let show = 0;

	var selected: DataBaseItem = demos[0];
	$: src = 'footage/' + selected.url + '-large.jpg';

	let demoCarousel: Carousel;
	let gamesCarousel: Carousel;
	let toolsCarousel: Carousel;

	onMount(() => {
		console.log('onMount');
		update(demos[0]);
	});

	function goBack() {
		console.log('goBack()');
		goto('/');
	}

	function update(item: DataBaseItem) {
		demoCarousel.setActive(item.title);
		gamesCarousel.setActive(item.title);
		toolsCarousel.setActive(item.title);
		selected = item;
		goto('#top');
	}

	function handleMessage(event: CustomEvent) {
		if (!event.detail.locked) {
			update(event.detail);
			show += 1;
		}
	}

	async function runTitle() {
		console.log('Setting up audio...');
		await $proxy.setupAudio();

		console.log('Running ' + selected.title + '...');
		$amiga.powerOff();
		console.log('Configuring CHIP: ' + selected.memory[0]);
		$amiga.configure($proxy.OPT_CHIP_RAM, selected.memory[0]);
		console.log('Configuring SLOW: ' + selected.memory[1]);
		$amiga.configure($proxy.OPT_SLOW_RAM, selected.memory[1]);
		console.log('Configuring FAST: ' + selected.memory[2]);
		$amiga.configure($proxy.OPT_FAST_RAM, selected.memory[2]);
		for (let i = 0; i < selected.adf.length; i++) {
			console.log('Inserting disk ' + i + ': ' + selected.adf[i]);
			$proxy.insert(selected.adf[i], i);
		}
		$amiga.run();
		goto('/emulator');
	}
</script>

<body class="h-screen flex flex-col bg-black text-white scroll-smooth overflow-y-scroll">
	<div id="top" class="">
		<div class="relative">
			<!--<img class="absolute top-0 left-0 w-full" src="footage/blank-large.png" alt="Alt" />-->
			<!--
			<div class="flex pb-5 z-40">
				<Button on:click={goBack}><FaAngleLeft /></Button>
			</div>
			-->
			{#key show}
				<div in:fade={{ duration: 1000 }}>
					<div class="grid grid-cols-1">
						<img class="z-10 col-start-1 row-start-1 brightness-90 blur-[2px]" {src} alt="Bg" />
						<img class="z-20 col-start-1 row-start-1" src="footage/blank-large.png" alt="Alt" />
						<div class="z-30 col-start-1 row-start-1 pt-4 px-6">
							<div class="font-sofia-extra text-8xl">{selected.title}</div>
							<div class="font-sofia-semi text-2xl pb-10">{selected.subtitle}</div>
							<div class="flex font-josefin text-lg w-2/3 pb-5">{selected.description}</div>
							<div class="pb-5">
								<Button on:click={runTitle} label="Start" />
							</div>
						</div>
					</div>
				</div>
			{/key}
			<div class="" />
		</div>
	</div>
	<div class="relative border-none border-red-500 -top-10 z-40">
		<!-- <img class="fixed z-50 border-none" src="footage/transparent-large.png" alt="Alt" />-->
		<div class="mt-10">
			<Carousel
				category="Demos"
				bind:this={demoCarousel}
				items={demos}
				on:message={handleMessage}
			/>
			<Carousel
				bind:this={gamesCarousel}
				category="Games"
				items={games}
				on:message={handleMessage}
			/>
			<Carousel
				bind:this={toolsCarousel}
				category="Tools"
				items={tools}
				on:message={handleMessage}
			/>
		</div>
	</div>

	<Logo />
</body>
