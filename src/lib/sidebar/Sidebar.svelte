<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import SidebarSection from '$lib/sidebar/SidebarSection.svelte';
	import { fade } from 'svelte/transition';
	import { layout, showShell, showSettings, debugDma } from '$lib/stores';
	import { poweredOn, running } from '$lib/stores';

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
	let controlItems = [
		{ id: 'pause', icon: 'icons/pauseIcon.png' },
		{ id: 'reset', icon: 'icons/resetIcon.png' },
		{ id: 'power', icon: 'icons/powerIcon.png' }
	];
	const settings = { id: 'settings', icon: 'icons/settingsIcon.png' };
	const shell = { id: 'shell', icon: 'icons/retroShellIcon.png' };
	const monitor = { id: 'monitor', icon: 'icons/monitorIcon.png' };
	const layoutButton = { id: 'layout', icon: 'icons/layoutIcon.png' };
	const layoutItems = [
		{ id: 'aspect', icon: 'icons/layoutAspectIcon.png' },
		{ id: 'fit', icon: 'icons/layoutFitIcon.png' },
		{ id: 'full', icon: 'icons/layoutFullIcon.png' }
	];

	$: layoutButton.icon =
		$layout == 'full'
			? 'icons/layoutFullIcon.png'
			: $layout == 'aspect'
			? 'icons/layoutAspectIcon.png'
			: 'icons/layoutFitIcon.png';

	$: if (!$poweredOn) {
		controlItems = [{ id: 'power', icon: 'icons/powerIcon.png' }];
	} else if ($running) {
		controlItems = [
			{ id: 'pause', icon: 'icons/pauseIcon.png' },
			{ id: 'reset', icon: 'icons/resetIcon.png' },
			{ id: 'power', icon: 'icons/powerIcon.png' }
		];
	} else {
		controlItems = [
			{ id: 'pause', icon: 'icons/runIcon.png' },
			{ id: 'reset', icon: 'icons/resetIcon.png' },
			{ id: 'power', icon: 'icons/powerIcon.png' }
		];
	}
</script>

<div transition:fade={{ duration }}>
	<div class="absolute top-0 left-0 h-full bg-gray-500/40 flex flex-col w-16 items-center">
		<div class="w-10 mt-2 flex flex-col space-y-1">
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
				item={layoutButton}
				subitems={layoutItems}
			/>
		</div>
	</div>
</div>
