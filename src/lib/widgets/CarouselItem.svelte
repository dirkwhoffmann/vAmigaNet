<svelte:options accessors={true}/>

<script lang="ts">

	import { romcrc } from '$lib/stores';

	export let title = '???';
	export let src = '';
	export let active = false;
	export let locked = true;
	export let aros = true;
	
	$: isLocked = $romcrc == 0 || (!aros && $romcrc == 1062194186);

	$: textcol = active ? "text-white" : "text-gray-400";
	$: border = active ? "border-white border-2" : "border-gray-700 border-2";
	$: opacity = isLocked ? "opacity-40" : "opacity-100";
	$: brightness = (active && !isLocked) ? "brightness-125" : "brightness-75";
</script>

<div class="">
	<div class="p-1">
		<img class="rounded border-solid {border} {brightness} {opacity}" {src} alt={title} />
		{#if isLocked}
			<img class="absolute top-0 left-0 invert opacity-40" src="footage/lock.png" alt="" />
		{/if}
	</div>
	<div class="p-1">
		<div class="font-josefin text-xl justify-center">
			<div class="flex justify-center {textcol}">{title}</div>
		</div>
	</div>
</div>
