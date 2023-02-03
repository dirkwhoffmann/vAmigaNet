<script lang="ts">
    import { createEventDispatcher } from 'svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import { fade, fly, scale, slide } from 'svelte/transition';

	export let expanded = false;
    export let item = { id: '', icon: '' };
	export let subitems = [{ id: '', icon: '' }];

    const dispatch = createEventDispatcher();

	function expand() {
		console.log('item: expand = ' + expanded);
		expanded = !expanded;
	}

    function select(e: Event) {
		e.preventDefault();
		console.log('SidebarSection: Click on ' + e.detail.sender );
        expanded = false;
		dispatch('select', { sender: e.detail.sender });
	}
</script>

<div class="flex">
	<div>
		<div class="border-0">
			<SidebarButton
				on:select={select}
				highlighted={expanded}
				{item}
			/>
		</div>
	</div>
	{#if expanded}
		<div transition:fade={{ duration: 200 }}>
			<div class="border-0 flex space-x-1 mx-1">
                {#each subitems as item}
                <div class="border-0">
					<SidebarButton on:select={select} {item} />
				</div>
                {/each}
			</div>
		</div>
	{/if}
</div>
