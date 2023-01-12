<script lang="ts">
	import '../../app.css';
	import Carousel from '$lib/Carousel.svelte';
	import '@splidejs/svelte-splide/css';

	const demos = [
		{
			url: 'footage/batmanrises-small.jpg',
			description: 'Batman Rises'
		},
		{
			url: 'footage/rinkadink-small.jpg',
			description: 'Rink a Dink'
		},
		{
			url: 'footage/desertdreams-small.jpg',
			description: 'Desert Dreams'
		},
		{
			url: 'footage/inebriation-small.jpg',
			description: 'Absolute Inebriation'
		},
		{
			url: 'footage/eon-small.jpg',
			description: 'Eon'
		},
	];

	const games = [
		{
			url: 'footage/traprunner-small.jpg',
			description: 'Trap Runner (Demo)'
		},
		{
			url: 'footage/celtic-small.jpg',
			description: 'Celtic Heart (Demo)'
		},
		{
			url: 'footage/defender-small.jpg',
			description: 'Defender of the Crown'
		},
	];

	const tools = [
		{
			url: 'footage/sysinfo-small.jpg',
			description: 'Sysinfo 4.4'
		},
		{
			url: 'footage/testkit-small.jpg',
			description: 'Amiga Test Kit'
		},
		{
			url: 'footage/diagrom-small.jpg',
			description: 'Amiga DiagROM'
		},
	];

</script>

<body class="h-screen bg-black text-white">
	<!--<Toolbar  bgcolor={tbcolor1} />-->
	<div class="">
		<img class="w-full" src="defender.jpg" />
		<div>
			<div class="absolute top-10 left-10">
				<div class="font-sofia-extra text-8xl">Defender of the Crown</div>
				<div class="font-sofia-semi text-2xl pb-10">Cinemaware (1986)</div>
				<div class="flex font-josefin text-lg w-1/3">
					Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was
					Cinemaware's first game, and was originally released for the Commodore Amiga in 1986,
					setting a new standard for graphic quality in home computer games.
				</div>
			</div>
		</div>
		<div class="pb-2" />

		<Carousel category="Demos" items={demos} />
		<Carousel category="Games" items={games} />
		<Carousel category="Tools" items={tools} />
	</div>
</body>
