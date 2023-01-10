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
		{
			url: 'small-aros.jpg',
			description: 'Aros Kickstart Replacement'
		},
		{
			url: 'small-kick12.jpg',
			description: 'Kickstart 1.2'
		},
		{
			url: 'small-kick13.jpg',
			description: 'Kickstart 1.3'
		},
		{
			url: 'small-kick20.jpg',
			description: 'Kickstart 2.04'
		},
		{
			url: 'small-kick31.jpg',
			description: 'Kickstart 3.1'
		},
		{
			url: 'small-hyperion.jpg',
			description: 'Hyperion Kickstart 3.2'
		}
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
