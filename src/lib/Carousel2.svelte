<script>
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import CarouselItem from './CarouselItem.svelte';

	const options = {
		type: 'fade',
		perPage: 1,
		perMove: 1,
		pagination: false,
		gap: '1rem',
		}
	const images = [
		{
			url: 'bg_defender.jpg',
			description: 'Defender of the Crown'
		},
		{
			url: 'bg_batman.jpg',
			description: 'Batman Rises'
		},
		{
			url: 'bg_rinkadink.jpg',
			description: 'Rink a Dink'
		},
	];
</script>

<Splide
	options={options}
>
	{#each images as src, imageIndex (src)}
		<SplideSlide>
			<CarouselItem src={src.url} alt={src.description} />
		</SplideSlide>
	{/each}
</Splide>
