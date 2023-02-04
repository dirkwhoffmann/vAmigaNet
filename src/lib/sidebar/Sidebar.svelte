<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import SidebarSection from '$lib/sidebar/SidebarSection.svelte';
	import { fade } from 'svelte/transition';

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
		sel = e.detail.sender == sel ? '' : e.detail.sender;
		console.log(sel + ' selected');
		dispatch('select', { sender: e.detail.sender });
	}

	const vamiga = { id: 'vamiga', icon: 'icons/vamigaIcon.png' };
	const control = { id: 'control', icon: 'icons/controlIcon.png' };
	const controlItems = [
		{ id: 'pause', icon: 'icons/pauseIcon.png' },
		{ id: 'reset', icon: 'icons/resetIcon.png' },
		{ id: 'power', icon: 'icons/powerIcon.png' }
	];
	const settings = { id: 'settings', icon: 'icons/settingsIcon.png' };
	const shell = { id: 'shell', icon: 'icons/retroShellIcon.png' };
	const layout = { id: 'layout', icon: 'icons/layoutIcon.png' };
	const monitor = { id: 'monitor', icon: 'icons/monitorIcon.png' };
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
	<div><SidebarButton on:select={expand} {opacity} item={vamiga} /></div>
	{#if expanded}
		<div class="z-50 relative space-y-1" transition:fade={{ duration }}>
			<SidebarSection on:select={select} expanded={sel=='control'} item={control} subitems={controlItems} />
            <SidebarButton on:select={select} item={settings} />
			<SidebarButton on:select={select} item={shell} />
			<SidebarButton on:select={select} item={monitor} />
            <SidebarSection on:select={select} expanded={sel=='layout'} item={layout} subitems={layoutItems} />
		</div>
	{/if}
</div>
