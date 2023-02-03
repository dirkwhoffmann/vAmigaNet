<script lang="ts">
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import { fade, fly, scale, slide } from 'svelte/transition';

	export let disabled = false;
	export let alt = 'Sidebar Item';
	export let icon = '';
    export let id = '';
	export let expanded = false;

	function expand() {
		console.log('item: expand = ' + expanded);
		expanded = !expanded;
	}
</script>

<div class="flex">
	<slot />
	{#if expanded}
		<div transition:fade={{ duration: 200 }} class="flex">
			<!--<div transition:slide={{x: -150}} class="flex">-->
			<slot name="subitems" />
		</div>
	{/if}
</div>
