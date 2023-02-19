<script lang="ts">
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import Carousel from '$lib/widgets/Carousel.svelte';
	import { demos, games, tools } from '$lib/database';
	import { proxy, audio, amiga } from '$lib/stores';
	import { db, type RomEntry } from '$lib/db/db';
	import { liveQuery } from 'dexie';
	import Sedcard from '$lib/Sedcard.svelte';

	let show = 0;

	// var selected: DataBaseItem = demos[0];
	var selected: DataBaseItem | null = null;
	$: src = 'footage/' + (selected?.url ?? '') + '-large.jpg';

	let demoCarousel: Carousel;
	let gamesCarousel: Carousel;
	let toolsCarousel: Carousel;

    let showSedcard = false;

	onMount(() => {
		console.log('onMount');
		// update(demos[0]);
	});

	function update(item: DataBaseItem) {
		if (activeTab == 0) demoCarousel.setActive(item.title);
		if (activeTab == 1) gamesCarousel.setActive(item.title);
		if (activeTab == 2) toolsCarousel.setActive(item.title);
		selected = item;
	}

	function handleMessage(event: CustomEvent) {
		update(event.detail);
        showSedcard = true;
	}

	async function runTitle() {
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
	}

	let tabs = ['Demos', 'Games', 'Tools'];
	let activeTab = 0;
	$: console.log('activeTab = ', activeTab);
	$: console.log('showSedcard = ', showSedcard);
	const debug = ''; // 'border-2';
</script>

<div class="modal" class:modal-open={showSedcard}>
	<div class="modal-box w-11/12 min-h-[380px] max-w-6xl bg-black">
		<Sedcard bind:show={showSedcard} {selected} />
	</div>
</div>

<div class="grow h-full flex flex-col justify-center overflow-auto" in:fade>

<!-- <div in:fade class="relative bg-transparent grow flex flex-col items-center justify-center {debug}">-->
	<!--
	<div class="flex items-center space-x-2">
		<div class="{debug} tabs tabs-boxed flex grow">
			{#each tabs as tab, i}
				<button class="tab w-24" class:tab-active={activeTab == i} on:click={() => (activeTab = i)}
					>{tab}</button
				>
			{/each}
		</div>
	</div>
-->
	<div class="relative h-full">
		<div class="w-hull bg-gray-500/50 text-2xl p-1 font-josefin">Demos</div>
			<Carousel
				category="Demos"
				bind:this={demoCarousel}
				items={demos}
				on:message={handleMessage}
			/>
			<div class="w-hull bg-gray-500/50 text-2xl p-1 font-josefin">Games</div>
			<Carousel
				bind:this={gamesCarousel}
				category="Games"
				items={games}
				on:message={handleMessage}
			/>
			<div class="w-hull bg-gray-500/50 text-2xl p-1 font-josefin">Tools</div>
			<Carousel
				bind:this={toolsCarousel}
				category="Tools"
				items={tools}
				on:message={handleMessage}
			/>
	</div>
</div>
