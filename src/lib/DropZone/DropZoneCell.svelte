<script lang="ts">
	import { createEventDispatcher } from 'svelte';
    import { invert } from '$lib/stores';
    import FaTimes from 'svelte-icons/fa/FaTimes.svelte'
	import { audio } from '$lib/stores';

    export let id: number;
	export let name: string;
	export let enabled = false;
    export let selected = false;
    export let icon1 = "icons/disk.png";
	export let icon2 = "icons/disk.png";
	export let opacity = 'opacity-50';

    $: opac = selected ? 'opacity-100' : 'opacity-50';
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

    async function mouseClick(event: MouseEvent) {
        event.preventDefault();
		await $audio.setup();
        dispatch('drive', name);
    }

</script>

<div class="p-4 rounded-xl bg-primary/90">
	<div class="flex flex-col items-center">
		<div
			class="h-32 w-32 border-2 border-primary-content rounded-xl p-5 {bopac}"
			on:mouseenter={mouseEnter}
			on:mouseleave={mouseLeave}
			on:mousedown={mouseClick}
		>
        {#if !enabled}
            <div class="w-full h-full opacity-50 text-primary-content"><FaTimes /></div>
        {:else if selected}
            <img class="{$invert} {opac}" src={icon1} alt="Icon"/>
		{:else if icon2 !== ''}
			<img class="{$invert} {opac}" src={icon2} alt="Icon"/>
		{/if}
		</div>
		<div class="font-azaret text-primary-content text-xl">{name}</div>
	</div>
</div>
