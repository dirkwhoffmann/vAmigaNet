<script lang="ts">
	import '../app.css';
	import { onMount } from 'svelte';
	import FaRegClock from 'svelte-icons/fa/FaRegClock.svelte';
	import Toolbar from '$lib/Toolbar.svelte';
	import MySiema from '$lib/MySiema.svelte';

	onMount(() => {
		console.log('onMount');
	});
</script>

<body class="h-screen bg-black text-white">
	<!--<Toolbar  bgcolor={tbcolor1} />-->
	<div class="">
		<img class="w-full" src="defender.jpg" />
		<div class="absolute top-10 left-10">
			<div class="font-sofia-extra text-8xl">Defender of the Crown</div>
			<div class="font-sofia-semi text-2xl pb-10">Cinemaware (1986)</div>
			<div class="flex font-josefin text-lg w-1/3">
				Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was
				Cinemaware's first game, and was originally released for the Commodore Amiga in 1986,
				setting a new standard for graphic quality in home computer games.
			</div>
		</div>

		<MySiema />
	</div>
</body>
