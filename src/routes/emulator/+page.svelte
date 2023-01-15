<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { vAmiga } from "$lib/stores";

	let showMenu = false
	onMount(() => {
		console.log('onMount()');
	});

</script>



<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div>
		<div class="absolute z-30 fixed w-screen h-16 bg-white/30">
			<a href="/">back</a>
			<button on:click={()=>$vAmiga._wasm_get_cpu_cycles()}>inc</button>
		</div>
	</div>	 


	<div class="flex justify-center absolute w-full h-full">
		<div class="absolute z-20 w-2/3 h-2/3 bg-gray-600"> 
				<canvas id="canvas" oncontextmenu="event.preventDefault()"></canvas>
		</div>
	</div>

</body>
