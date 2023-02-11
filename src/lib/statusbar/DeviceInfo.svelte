<script lang="ts">
	import { createEventDispatcher } from 'svelte';

	export let cylinder = 99;
    export let hasDisk = true;
    export let motor = false;
    export let writing = false;

    const gray = 'border-gray-600 border-opacity-100 bg-gradient-to-b from-gray-600 to-gray-500';
    const green = 'border-gray-600 border-opacity-100 bg-gradient-to-b from-green-500 to-green-400';
    const red = 'border-gray-600 border-opacity-75 opacity-100 bg-gradient-to-b from-red-500 to-red-400';

    $: src = hasDisk ? 'icons/floppy.png' : 'icons/floppy.png';
    $: bg = motor ? (writing ? red : green) : gray;

	// const dispatch = createEventDispatcher<{push:{sender:string}}>();

	function click(e: Event) {
		e.preventDefault();
		// dispatch('push', { sender: (e.target as HTMLElement).id });
	}
</script>

<div class="flex">
	<div class="flex h-8 py-1.5 px-3">
		<div class="border-0 h-full pr-2 flex flex-col justify-between items-center">
			<div
				class="h-1/2 border-[1.5px] rounded-sm w-6 {bg}"
			/>
			<div class="border-0 leading-none text-[7pt] text-gray-300 ">{cylinder}</div>
		</div>
		<img class="border-0 h-full invert opacity-50" {src} alt="Floppy icon" />
	</div>
</div>
