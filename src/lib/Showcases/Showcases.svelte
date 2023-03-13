<script lang="ts">
	import { fade } from 'svelte/transition';
	import type { DataBaseItem } from '$lib/types';
	import Carousel from '$lib/Showcases/Carousel.svelte';
	import { demos, games, tools } from './database';
	import Sedcard from './Sedcard.svelte';

	let selected: DataBaseItem | null = null;
	let showSedcard = false;

	let demoCarousel: Carousel;
	let gamesCarousel: Carousel;
	let toolsCarousel: Carousel;

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

	let activeTab = 0;

</script>

<div class="modal" class:modal-open={showSedcard}>
	<div class="modal-box w-11/12 min-h-[380px] max-w-6xl bg-black">
		<Sedcard bind:show={showSedcard} {selected} />
	</div>
</div>

<div class="grow h-full flex flex-col justify-center overflow-auto" in:fade>
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
