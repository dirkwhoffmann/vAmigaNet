<script lang="ts">
	import type { DataBaseItem } from '$lib/types';
	import { romcrc } from '$lib/stores';
	import { fade } from 'svelte/transition';
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import { createEventDispatcher } from 'svelte';
	import CarouselItem from '$lib/Showcases/CarouselItem.svelte';

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

<div class="p-4" in:fade>
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
					locked={item.incompatibleRoms.includes($romcrc)}
				/>
			</SplideSlide>
		{/each}
	</Splide>
	<div class="py-2" />
</div>
