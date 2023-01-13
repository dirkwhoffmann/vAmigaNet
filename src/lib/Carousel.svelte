<script>
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import { createEventDispatcher } from 'svelte';
	import CarouselItem from './CarouselItem.svelte';

	export let category = '';
	export let items = [{ url: '', title: '', subtitle: '', description: ''}];

	const dispatch = createEventDispatcher();

	const options = {
		type: 'slide',
		perPage: 5,
		perMove: 1,
		pagination: false,
		gap: '1rem',
	};
</script>

<div class="font-sofia-semi text-4xl mx-2 px-5 bg-gradient-to-r from-gray-600 to-black">{category}</div>
<div class="p-4">
	<Splide {options}
	on:click={ e => { 
		console.log( e.detail.Slide.index );
		dispatch('message', items[e.detail.Slide.index]);
		} }
	>
		{#each items as src}
			<SplideSlide>
				<CarouselItem src='footage/{src.url}-small.jpg' title={src.title} subtitle={src.subtitle} />
			</SplideSlide>
		{/each}
	</Splide>
	<div class="py-2"></div>
</div>
