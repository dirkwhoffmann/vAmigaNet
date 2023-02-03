<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarItem from '$lib/sidebar/SidebarItem.svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import SidebarSection from '$lib/sidebar/SidebarSection.svelte';
	import { fly, fade, slide, scale } from 'svelte/transition';

	let expanded = false;
	let sel = '';
	let duration = 200;
	let opacity = 'opacity-20';

	const dispatch = createEventDispatcher();

	function expand() {
		sel = '';
		console.log('expand = ' + expanded);
		if (expanded) {
			expanded = false;
			opacity = 'opacity-20';
		} else {
			expanded = true;
			opacity = 'opacity-100';
		}
	}

	function select(e: Event) {
		e.preventDefault();
		sel = e.detail.sender;
		console.log(sel + ' selected');
		dispatch('select', { sender: sel });
	}

	const control = { id: 'control', icon: 'icons/controlIcon.png' };
	const controlItems = [
		{ id: 'pause', icon: 'icons/pauseIcon.png' },
		{ id: 'reset', icon: 'icons/resetIcon.png' },
		{ id: 'power', icon: 'icons/powerIcon.png' }
	];
	const layout = { id: 'layout', icon: 'icons/layoutIcon.png' };
	const layoutItems = [
		{ id: 'aspect', icon: 'icons/layoutAspectIcon.png' },
		{ id: 'fit', icon: 'icons/layoutFitIcon.png' },
		{ id: 'full', icon: 'icons/layoutFullIcon.png' }
	];

</script>

{#if expanded}
	<div
		class="absolute top-0 left-0 h-screen bg-gray-500/40 flex flex-col w-14"
		transition:fade={{ duration }}
	/>
{/if}
<div class="z-50 absolute top-0 left-0 p-2 flex flex-col space-y-1">
	<div><SidebarButton id="vamiga" on:select={expand} {opacity} icon="icons/vamigaIcon.png" /></div>
	{#if expanded}
		<div class="z-50 relative space-y-1" transition:fade={{ duration }}>
			<SidebarSection on:select={select} expanded={sel=='control'} item={control} subitems={controlItems} />
            <SidebarButton id="settings" on:select={select} icon="icons/settingsIcon.png" />
			<SidebarButton id="shell" on:select={select} icon="icons/retroShellIcon.png" />
			<SidebarButton id="monitor" on:select={select} icon="icons/monitorIcon.png" />
            <SidebarSection on:select={select} expanded={sel=='layout'} item={layout} subitems={layoutItems} />
		</div>
	{/if}
</div>
