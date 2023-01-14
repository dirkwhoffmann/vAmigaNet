<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';

	onMount(() => {
		console.log('onMount()');
	});

</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="flex justify-center absolute w-full h-full">
		<div class="absolute z-50 w-2/3 h-2/3 bg-gray-600"> 
			<script src="vAmiga.js"></script>
			<canvas></canvas>
		</div>
	</div>

</body>
