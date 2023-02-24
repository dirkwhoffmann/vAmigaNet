<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import { proxy, amiga, retroShell, diskController } from '$lib/stores';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { darkTheme } from '$lib/stores';
	import { enhance } from '$app/forms';

	export let name = '???';
    export let selected = false;
    export let enabled = false; 

    const dispatch = createEventDispatcher<{ drive: string }>();

    function mouseEnter(event: MouseEvent) {
		event.preventDefault();
        if (enabled) selected = true; 
	}

	function mouseLeave(event: MouseEvent) {
		event.preventDefault();
        selected = false;
	}

    function mouseClick(event: MouseEvent) {
        event.preventDefault();
        console.log("mouseClick");
        dispatch('drive', name );
    }

</script>

<div class="p-4 rounded-xl bg-primary/50">
	<div class="flex flex-col items-center">
		<div
			class="h-32 w-32 border-2 rounded-xl p-5"
			on:mouseenter={mouseEnter}
			on:mouseleave={mouseLeave}
			on:mousedown={mouseClick}
		>
        {#if selected}
			<img class={$darkTheme ? 'invert' : ''} src="icons/disk.png" alt="Floppy Disk" transition:fade />
        {/if}
		</div>
		<div class="font-azaret text-primary-content text-xl">{name}</div>
	</div>
</div>
