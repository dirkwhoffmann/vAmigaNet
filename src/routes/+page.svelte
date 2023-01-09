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
	
    <div class="relative">
        <img class="w-full brightness-50" src="defender2.jpg" />
		<!--
		<h1 class="absolute text-5xl text-white top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2">
            KindaCode.com</h1>
        <h2 class="absolute text-3xl text-amber-400 bottom-4 left-1/2 -translate-x-1/2">Bottom Center</h2>
        <h3 class="absolute text-2xl text-blue-300 top-5 left-5">Top Left</h3>
		<h3 class="absolute text-2xl text-green-300 bottom-5 right-5">Bottom Right</h3>
		-->
		<div class="absolute top-10 left-10">
			<div class="font-rubik text-5xl">Defender of the Crown</div>
			<div class="font-josefin text-2xl">Cinemaware</div>
			<div class="font-josefin text-1xl w-1/2">Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was Cinemaware's first game, and was originally released for the Commodore Amiga in 1986, setting a new standard for graphic quality in home computer games.
		</div>
    </div>

<MySiema />
</body>
