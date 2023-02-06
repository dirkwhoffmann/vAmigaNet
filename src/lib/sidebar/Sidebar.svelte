<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import SidebarSection from '$lib/sidebar/SidebarSection.svelte';
	import { fade } from 'svelte/transition';
	import { showSidebar, showShell, showSettings, debugDma } from '$lib/stores';

	// export let expanded = false;
	let sel = '';
	let duration = 200;
	let opacity = 'opacity-20';

	const dispatch = createEventDispatcher();

	function select(e: Event) {
		e.preventDefault();
		sel = e.detail.sender == sel ? '' : e.detail.sender;
		console.log('sender: ', e.detail.sender, ' state: ', e.detail.state);
		dispatch('select', { sender: e.detail.sender, state: e.detail.state });
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
	const monitor = { id: 'monitor', icon: 'icons/monitorIcon.png' };
	const layout = { id: 'layout', icon: 'icons/layoutIcon.png' };
	const layoutItems = [
		{ id: 'aspect', icon: 'icons/layoutAspectIcon.png' },
		{ id: 'fit', icon: 'icons/layoutFitIcon.png' },
		{ id: 'full', icon: 'icons/layoutFullIcon.png' }
	];
</script>

<div transition:fade={{ duration }}>
	<div class="absolute top-0 left-0 h-full mt-1 bg-gray-500/40 flex flex-col w-16" />
	<div class="absolute top-0 left-0 w-16 mt-3 ml-3.5 flex flex-col space-y-1">
		<SidebarSection
			on:select={select}
			expanded={sel == 'control'}
			item={control}
			subitems={controlItems}
		/>
		<SidebarButton on:select={select} item={settings} highlighted={$showSettings} />
		<SidebarButton on:select={select} item={shell} highlighted={$showShell} />
		<SidebarButton on:select={select} item={monitor} highlighted={$debugDma} />
		<SidebarSection
			on:select={select}
			expanded={sel == 'layout'}
			item={layout}
			subitems={layoutItems}
		/>
	</div>
</div>
