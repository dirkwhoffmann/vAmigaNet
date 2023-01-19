<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import Carousel from '$lib/Carousel.svelte';
	import Icon from '$lib/widgets/Icon.svelte';
	import * as animateScroll from 'svelte-scrollto';
	import '@splidejs/svelte-splide/css';

	let show = 0;

	const demos = [
		{
			url: 'batmanrises',
			title: 'Batman Rises',
			subtitle: 'The Batman Group',
			description:
				'Batman Rises is a demo released in December 2022 at Posadas Party Autumn Edition. It quickly caught public attention and is considered by many to be one of the best demos ever made for the Commodore Amiga.'
		},
		{
			url: 'rinkadink',
			title: 'Rink a Dink - Redux',
			subtitle: 'Lemon',
			description:
				'This demo has been released by Lemon at Revision 2013 and has become extremely popular over time. We have used it since the early days of vAmiga to extensively test the emulator.'
		},
		{
			url: 'desertdreams',
			title: 'Desert Dreams',
			subtitle: 'Kefrens',
			description:
				'This demo was released in April 1993. It ranked 1st in the Gathering 1993 Amiga Demo Competition.'
		},
		{
			url: 'inebriation',
			title: 'Absolute Inebriation',
			subtitle: 'Virtual Dreams & Fairlight',
			description:
				'This demo was released in December of 1992. It was the first production of Virtual Dreams, a Finnish-based Amiga demo group. The group reached their breakthrough in their time spent as the demo section of Fairlight.'
		},
		{
			url: 'eon',
			title: 'Eon',
			subtitle: 'The Black Lotus',
			description:
				'This demo is one of the best ever created for the Commodore Amiga. It shows impressively what the machine is capable of when its potential is exploited to the max.'
		}
	];

	const games = [
		{
			url: 'traprunner',
			title: 'Trap Runner',
			subtitle: 'Night Owl Design',
			description:
				'Trap Runner is a classic platform game with few twists. Mind traps, obstacles and monsters. Collect items to increase your score, gain extra lives or fulfil one of the special missions. Two of four levels a world have a mission to accomplish. The game runs on any OCS/ECS Amiga, with 1MB RAM from Kickstart 1.2 onwards.'
		},
		{
			url: 'celtic',
			title: 'Celtic Heart',
			subtitle: 'Night Owl Design',
			description:
				'This game was written in the beginning of 2019, largely based on the Trap Runner engine. It has a medieval setting, where you are playing the celtic knight Eric on his task to save the kingdom from an evil force.'
		},
		{
			url: 'paccer',
			title: 'Paccer',
			subtitle: 'Dirk W. Hoffmann',
			description:
				'This game is a Pac-Man clone that was originally released on Fish Disk 223. I implemented this game myself many years ago on my Amiga 500 with the Aztec C compiler and DPaint. Unfortunately, I lost the source code when my parents cleaned up their attic. Luckily, the game survived on the Internet.'
		},
		{
			url: 'defender',
			title: 'Defender of the Crown',
			subtitle: 'Cinemaware',
			description:
				"Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was Cinemaware's first game, and was originally released for the Commodore Amiga in 1986, setting a new standard for graphic quality in home computer games."
		}
	];

	const tools = [
		{
			url: 'sysinfo',
			title: 'Sysinfo 4.4',
			subtitle: 'Nic Wilson, Tobias Geijersson',
			description:
				'Sysinfo is a shareware program written completely in Assembler for the Motorola 68k equipped Amiga computers to benchmark system performance. Sysinfo shows which version of system software is present in ROM, which hardware is present, and which operating mode the hardware uses.'
		},
		{
			url: 'testkit',
			title: 'Amiga Test Kit',
			subtitle: 'Keir Fraser',
			description:
				'The Amiga Test Kit is a software-based solution for testing various components of a Commodore Amiga.'
		},
		{
			url: 'diagrom',
			title: 'Amiga DiagROM',
			subtitle: 'John Hertell',
			description:
				'The Amiga Diagnostic ROM is a hardware-based solution for testing Amiga hardware. On real machines, the Diagnostic ROM is used as a replacement for the Kickstart ROM on the motherboard. After powering on, the Amiga boots into a diagnostic menu. The ROM offers various test routines for checking different components.'
		}
	];

	var src = '';
	var title = '';
	var subtitle = '';
	var description = '';

	let demoCarousel: Carousel;
	let gamesCarousel: Carousel;
	let toolsCarousel: Carousel;

	onMount(() => {
		console.log('onMount');
		update(demos[0]);
	});

	function update(detail) {
		console.log(detail.description);
		demoCarousel.setActive(detail.title);
		gamesCarousel.setActive(detail.title);
		toolsCarousel.setActive(detail.title);
		src = 'footage/' + detail.url + '-large.jpg';
		title = detail.title;
		subtitle = detail.subtitle;
		description = detail.description;
	}

	function handleMessage(event) {
		console.log(event.detail.description);
		update(event.detail);
		animateScroll.scrollToTop();
		show += 1;
	}
</script>

<body class="h-screen flex flex-col bg-black text-white">
	<div class="">
		<img class="w-full" src="footage/blank-large.png" alt="Alt" />
		<div class="absolute top-5 left-10 flex pb-5 z-10">
			<a href="/" class="" title="Go to the main page">
				<button class=""><img class="h-11" src="va-icon.png" alt="vAmiga Icon" /></button></a
			>
			<div class="font-sofia-extra text-3xl px-3 pt-1 text-gray-700">vAmiga Online</div>
		</div>
		{#key show}
			<div in:fade={{ duration: 1000 }}>
				<div class="">
					<img
						class="absolute top-0 left-0 w-full brightness-90 blur-[2px]"
						{src}
						alt="Background"
					/>
					<img class="absolute top-0 left-0  w-full" src="footage/blank-large.png" alt="Alt" />
				</div>
				<div class="">
					<div class="absolute top-[5rem] left-10 w-full">
						<div class="font-sofia-extra text-8xl">{title}</div>
						<div class="font-sofia-semi text-2xl pb-10">{subtitle}</div>
						<div class="flex font-josefin text-lg w-1/2">{description}</div>
					</div>
				</div>
			</div>
		{/key}
		<div class=" pb-2" />
	</div>
	<div class="border-none border-red-500 flex-grow overflow-scroll">
		<img class="fixed z-50 border-none" src="footage/transparent-large.png" alt="Alt" />
		<div class="mt-10">
			<Carousel
				category="Demos"
				bind:this={demoCarousel}
				items={demos}
				on:message={handleMessage}
			/>
			<Carousel bind:this={gamesCarousel} category="Games" items={games} on:message={handleMessage} />
			<Carousel bind:this={toolsCarousel} category="Tools" items={tools} on:message={handleMessage} />
		</div>
	</div>
</body>
