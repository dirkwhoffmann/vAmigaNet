<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';

	let showMenu = false

	onMount(() => {
		console.log('onMount()');
	});

</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div>
	{#key show}
		<div class="aboslute z-30 fixed w-screen h-16 bg-white/30">
		</div>
	{/key}
	</div>	 


	<div class="flex justify-center absolute w-full h-full">
		<div class="absolute z-20 w-2/3 h-2/3 bg-gray-600"> 
			<script src="vAmiga.js"></script>
			<canvas></canvas>
		</div>
	</div>

</body>
