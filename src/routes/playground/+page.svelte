<script lang="ts">
	import '../../app.css';
	import Carousel from '$lib/Carousel.svelte';
	import '@splidejs/svelte-splide/css';

	const demos = [
		{
			url: 'footage/batmanrises-small.jpg',
			title: 'Batman Rises',
			subtitle: 'Batman Group'
		},
		{
			url: 'footage/rinkadink-small.jpg',
			title: 'Rink a Dink - Redux',
			subtitle: 'Lemon'
		},
		{
			url: 'footage/desertdreams-small.jpg',
			title: 'Desert Dreams',
			subtitle: 'Kefrens'
		},
		{
			url: 'footage/inebriation-small.jpg',
			title: 'Absolute Inebriation',
			subtitle: 'Virtual Dreams & Fairlight'
		},
		{
			url: 'footage/eon-small.jpg',
			title: 'Eon',
			subtitle: 'The Black Lotus'
		}
	];

	const games = [
		{
			url: 'footage/traprunner-small.jpg',
			title: 'Trap Runner (Demo)',
			subtitle: 'Retroguru'
		},
		{
			url: 'footage/celtic-small.jpg',
			title: 'Celtic Heart',
			subtitle: 'Night Owl Design'
		},
		{
			url: 'footage/defender-small.jpg',
			title: 'Defender of the Crown',
			subtitle: 'Cinemaware'
		}
	];

	const tools = [
		{
			url: 'footage/sysinfo-small.jpg',
			title: 'Sysinfo 4.4',
			subtitle: 'Nic Wilson, Tobias Geijersson'
		},
		{
			url: 'footage/testkit-small.jpg',
			title: 'Amiga Test Kit',
			subtitle: 'Keir Fraser'
		},
		{
			url: 'footage/diagrom-small.jpg',
			title: 'Amiga DiagROM',
			subtitle: 'John Hertell'
		}
	];
</script>

<body class="h-screen bg-black text-white">
	<div class="h-screen border-4 border-red-500 flex-col">
		<div class="border-4">
			<img class="h-full" src="defender.jpg" />
			<div class="">
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
		</div>
		<div class="bg-yellow-500 h-full border-4 border-blue-500">
			<div class="border-4">
			<Carousel category="Demos" items={demos} />
			<Carousel category="Games" items={games} />
			<Carousel category="Tools" items={tools} />
			</div>
		</div>
	</div>
</body>
