<script>
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import CarouselItem from './CarouselItem.svelte';

	export let category = '';
	export let items = [{ url: '', title: '', subtitle: ''}];

	const options = {
		type: 'slide',
		perMove: 1,
		pagination: false,
		gap: '1rem',
		fixedWidth: '16rem'
	};
</script>

<div class="font-sofia-semi text-4xl px-5 pt-5">{category}</div>
<div class="p-4">
	<Splide {options}>
		{#each items as src}
			<SplideSlide>
				<CarouselItem src={src.url} title={src.title} subtitle={src.subtitle} />
			</SplideSlide>
		{/each}
	</Splide>
</div>
