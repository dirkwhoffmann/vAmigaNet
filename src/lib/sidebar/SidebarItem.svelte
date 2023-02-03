<script lang="ts">
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import { fade, fly, scale, slide } from 'svelte/transition';

	export let expanded = false;

	function expand() {
		console.log('item: expand = ' + expanded);
		expanded = !expanded;
	}
</script>

<div class="flex">
	<div>
		<slot />
	</div>
	{#if expanded}
		<div transition:fade={{ duration: 200 }}>
			<slot name="subitems" />
		</div>
	{/if}
</div>
