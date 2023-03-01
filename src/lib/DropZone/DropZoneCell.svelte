<script lang="ts">
	import { createEventDispatcher } from 'svelte';
    import { dfConnected, dfHasDisk, invert } from '$lib/stores';
    import FaTimes from 'svelte-icons/fa/FaTimes.svelte'

    export let id: number;
	export let name: string;
    export let selected = false;
    
    let enabled = $dfConnected[id]; 
    let hasDisk = $dfHasDisk[id]; 
    
    $: opac = selected ? 'opacity-100' : hasDisk ? 'opacity-50' : 'opacity-0';
    $: bopac = enabled ? 'opacity-100' : 'opacity-50';

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

<div class="p-4 rounded-xl bg-primary/50 backdrop-blur">
	<div class="flex flex-col items-center">
		<div
			class="h-32 w-32 border-2 border-primary-content rounded-xl p-5 {bopac}"
			on:mouseenter={mouseEnter}
			on:mouseleave={mouseLeave}
			on:mousedown={mouseClick}
		>
        {#if !enabled}
            <div class="w-full h-full opacity-50 text-primary-content"><FaTimes /></div>
        {:else if selected || hasDisk}
            <img class="{$invert} {opac}" src="icons/disk.png" alt="Floppy Disk"/>
        {/if}
		</div>
		<div class="font-azaret text-primary-content text-xl">{name}</div>
	</div>
</div>
