<script lang="ts">
	import { fade } from 'svelte/transition';
	import Carousel from '$lib/widgets/Carousel.svelte';
	import { demos, games, tools } from '$lib/database';
	import { romcrc } from '$lib/stores';
	import Sedcard from '$lib/Sedcard.svelte';

	let show = 0;

	$: aros = $romcrc == 1062194186;

	var selected: DataBaseItem | null = null;
	$: src = 'footage/' + (selected?.url ?? '') + '-large.jpg';

	let demoCarousel: Carousel;
	let gamesCarousel: Carousel;
	let toolsCarousel: Carousel;

    let showSedcard = false;

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
