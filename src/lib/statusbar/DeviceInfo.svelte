<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import BarBox from './BarBox.svelte';

	export let cylinder = 99;
	export let hasDisk = true;
	export let motor = false;
	export let writing = false;

	/*
	const gray = 'border-gray-600 border-opacity-100 bg-gradient-to-b from-gray-600 to-gray-500';
	const green = 'border-gray-600 border-opacity-100 bg-gradient-to-b from-green-500 to-green-400';
	const red =
		'border-gray-600 border-opacity-75 opacity-100 bg-gradient-to-b from-red-500 to-red-400';
	*/
	const gray = '';
	const green = 'bg-gradient-to-b from-green-700 to-green-500';
	const red = 'bg-gradient-to-b from-red-700 to-red-500';

	$: src = hasDisk ? 'icons/floppy.png' : 'icons/floppy.png';
	$: bg = motor ? (writing ? red : green) : gray;

	// const dispatch = createEventDispatcher<{push:{sender:string}}>();

	function click(e: Event) {
		e.preventDefault();
		// dispatch('push', { sender: (e.target as HTMLElement).id });
	}
</script>

<BarBox {bg}>
		<img class="border-0 pr-1 py-1.5 h-full invert opacity-50" {src} alt="Floppy icon" />
		<div class="border-0 w-6 items-center pl-1 text-left leading-none text-sm text-gray-300">{cylinder}</div>
</BarBox>
