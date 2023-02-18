<script lang="ts">
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/db/db';
	import { browser } from '$app/environment';
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import { createEventDispatcher } from 'svelte';
	import CarouselItem from '$lib/widgets/CarouselItem.svelte';

	export let category = '';
	export let items: DataBaseItem[] = [];

	const dispatch = createEventDispatcher();
	const options = {
		type: 'slide',
		perPage: 5,
		perMove: 1,
		pagination: false,
		gap: '1rem'
	};

	let cmps: CarouselItem[] = [];
	
	export function setActive(name: string) {

		console.log('setActive: ' + category);
		cmps.forEach((element) => {
			console.log(element.title);
			element.active = element.title == name;
		});
	}

</script>

<div class="font-sofia-semi text-4xl mx-2 px-5 bg-gradient-to-r from-sky-700 to-transparent">
	{category}
</div>
<div class="p-4">
	<Splide
		{options}
		on:click={(e) => {
			if (e != undefined) {
				dispatch('message', items[e.detail.Slide.index]);
			}
		}}
	>
		{#each items as item, index }
			<SplideSlide>
				<CarouselItem
					bind:this={cmps[index]}
					src="footage/{item.url}-small.jpg"
					title={item.title}
					locked={item.locked}
					aros={item.aros}
				/>
			</SplideSlide>
		{/each}
	</Splide>
	<div class="py-2" />
</div>
