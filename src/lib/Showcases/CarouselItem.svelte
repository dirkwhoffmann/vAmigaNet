<svelte:options accessors={true} />

<script lang="ts">
	import FaLock from 'svelte-icons/fa/FaLock.svelte';

	export let title = '???';
	export let src = '';
	export let active = false;
	export let locked = false; 

	$: textcol = active ? 'text-white' : 'text-gray-400';
	$: border = active ? 'border-white border-2' : 'border-gray-700 border-2';
	$: opacity = '';
	$: brightness = active ? 'brightness-125' : '';
</script>

<div class="">
	<div class="p-1 relative">
		<img class="rounded border-solid {border} {brightness} {opacity}" {src} alt={title} />
		{#if locked}
		<div class="absolute top-0 left-0 h-full w-full flex justify-center items-center">
			<div class="w-12 h-12 text-gray-200 opacity-70"><FaLock /></div>	
		</div>
		{/if}
	</div>
	<div class="p-1">
		<div class="font-josefin text-xl justify-center">
			<div class="flex justify-center {textcol}">{title}</div> 
		</div>
	</div>
</div>
