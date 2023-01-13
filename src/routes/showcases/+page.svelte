<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import Carousel from '$lib/Carousel.svelte';
	import * as animateScroll from "svelte-scrollto";
	import '@splidejs/svelte-splide/css';

	const demos = [
		{
			url: 'batmanrises',
			title: 'Batman Rises',
			subtitle: 'Batman Group',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'rinkadink',
			title: 'Rink a Dink - Redux',
			subtitle: 'Lemon',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'desertdreams',
			title: 'Desert Dreams',
			subtitle: 'Kefrens',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'inebriation',
			title: 'Absolute Inebriation',
			subtitle: 'Virtual Dreams & Fairlight',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'eon',
			title: 'Eon',
			subtitle: 'The Black Lotus',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		}
	];

	const games = [
		{
			url: 'traprunner',
			title: 'Trap Runner (Demo)',
			subtitle: 'Retroguru',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'celtic',
			title: 'Celtic Heart',
			subtitle: 'Night Owl Design',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'paccer',
			title: 'Paccer',
			subtitle: 'Dirk W. Hoffmann',
			description:
				'My first computer game, written in C.',
		},
		{
			url: 'defender',
			title: 'Defender of the Crown',
			subtitle: 'Cinemaware',
			description:
				'Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was Cinemaware\'s first game, and was originally released for the Commodore Amiga in 1986, setting a new standard for graphic quality in home computer games.',
		}
	];

	const tools = [
		{
			url: 'sysinfo',
			title: 'Sysinfo 4.4',
			subtitle: 'Nic Wilson, Tobias Geijersson',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'testkit',
			title: 'Amiga Test Kit',
			subtitle: 'Keir Fraser',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		},
		{
			url: 'diagrom',
			title: 'Amiga DiagROM',
			subtitle: 'John Hertell',
			description:
				'Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr',
		}
	];

	var src ='';
	var title ='';
	var subtitle ='';
	var description = '';
	
	onMount(() => {

		console.log("onMount");
		update(demos[0])
	});

	function update(detail) {

		console.log(detail.description);
		src = "footage/" + detail.url + "-large.jpg";
		title = detail.title;
		subtitle = detail.subtitle;
		description = detail.description;
	}

	function handleMessage(event) {

		console.log(event.detail.description);
		update(event.detail);
		animateScroll.scrollToTop();
	}
	
</script>

<body class="h-screen bg-black text-white">
	<div class="">
		<img class="w-full" {src} alt ="Background"/>
		<div>
			<div class="absolute top-10 left-10">
				<div class="font-sofia-extra text-8xl">{title}</div>
				<div class="font-sofia-semi text-2xl pb-10">{subtitle}</div>
				<div class="flex font-josefin text-lg w-1/3">{description}</div>
			</div>
		</div>
		<div class="pb-2" />

		<Carousel category="Demos" items={demos} on:message={handleMessage} />
		<Carousel category="Games" items={games} on:message={handleMessage} />
		<Carousel category="Tools" items={tools} on:message={handleMessage} />
	</div>
</body>
