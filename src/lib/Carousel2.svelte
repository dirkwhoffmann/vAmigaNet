<script>
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import CarouselItem from './CarouselItem.svelte';

	const options = {
		type: 'slide',
		perPage: 5,
		perMove: 1,
		pagination: false,
		gap: '1rem',
		}
	const images = [
        /*
    {
			url: 'small-defender.jpg',
			description: 'Defender of the Crown'
		},
        */
		{
			url: 'small-batman.jpg',
			description: 'Batman Rises'
		},
		{
			url: 'small-eon.jpg',
			description: 'Eon'
		},
		{
			url: 'small-rinkadink.jpg',
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
