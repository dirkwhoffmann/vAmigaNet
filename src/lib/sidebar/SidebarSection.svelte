<script lang="ts">
	import SidebarButton from '$lib/Sidebar/SidebarButton.svelte';
	import { fade } from 'svelte/transition';
	export let expanded = false;
	export let item = { id: '', icon: '' };
	export let subitems = [{ id: '', icon: '' }];
</script>

<div class="flex">
	<div>
		<div class="border-0">
			<SidebarButton on:select active={expanded} {item} />
		</div>
	</div>
	{#if expanded}
		<div transition:fade={{ duration: 200 }}>
			<div class="flex space-x-1 mx-1">
				{#each subitems as item}
					<SidebarButton on:select {item} />
				{/each}
			</div>
		</div>
	{/if}
</div>
