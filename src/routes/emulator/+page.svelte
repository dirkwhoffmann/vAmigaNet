<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import Button from '$lib/widgets/Button.svelte';
	import { vAmiga } from "$lib/stores";
	import { goto } from '$app/navigation';

	let showMenu = false

	onMount(() => {
		console.log('onMount()');
	});

	function goBack() {
		console.log('goBack()');
		goto("/");
	}

	function doInc() {
		console.log('doInc()');
		$vAmiga._wasm_get_cpu_cycles();
	}

</script>



<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div>
		<div class="absolute z-30 fixed w-screen h-16 bg-white/30 space-x-2">
			<!-- <a href="/">back</a>-->
			<Button on:click={goBack} label="Back" width="w-16"></Button>
			<Button on:click={doInc} label="Inc" width="w-16"></Button>
		</div>
	</div>	 


	<div class="flex justify-center absolute w-full h-full">
		<div class="absolute z-20 w-2/3 h-2/3 bg-gray-600"> 
				<canvas id="canvas" oncontextmenu="event.preventDefault()"></canvas>
		</div>
	</div>

</body>
