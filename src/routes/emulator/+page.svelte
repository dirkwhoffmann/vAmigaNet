<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';

	let showMenu = false
	onMount(() => {
		console.log('onMount()');
	});

</script>

<svelte:head>
	<script type='text/javascript'>
		console.log("do the module thing ");
		calledRun=false;
		Module = {
			onRuntimeInitialized: function() {
				  console.log("onRuntimeInitialized"); 
			},
			canvas: (function() { return document.getElementById('canvas'); })()
		};
	</script>
	<script src="vAmiga.js"></script>
</svelte:head>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div>
		<div class="absolute z-30 fixed w-screen h-16 bg-white/30">
			<a href="/">back</a>
			<button on:click={()=>window['Module']._wasm_get_cpu_cycles()}>inc</button>
		</div>
	</div>	 


	<div class="flex justify-center absolute w-full h-full">
		<div class="absolute z-20 w-2/3 h-2/3 bg-gray-600"> 
				<canvas id="canvas" oncontextmenu="event.preventDefault()"></canvas>
		</div>
	</div>

</body>
