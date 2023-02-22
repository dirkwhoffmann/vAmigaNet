<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import SidebarSection from '$lib/sidebar/SidebarSection.svelte';
	import { fade } from 'svelte/transition';
	import { layout, showShell, showSettings, debugDma } from '$lib/stores';
	import { poweredOn, running, port1, port2 } from '$lib/stores';

	let sel = '';
	let duration = 200;
	let opacity = 'opacity-20';

	const dispatch = createEventDispatcher<{ select: { sender: string; state: boolean } }>();

	function select(event: CustomEvent<{ sender: string; state: boolean }>) {
		event.preventDefault();

		const sender = event.detail.sender;
		const state = event.detail.state;
		sel = sender == sel ? '' : sender;
		console.log('sender: ', sender, ' state: ', state);
		dispatch('select', { sender: sender, state: state });
	}

	const vamiga = { id: 'vamiga', icon: 'icons/vamigaIcon.png' };
	const control = { id: 'control', icon: 'icons/controlIcon.png' };
	let controlItems = [
		{ id: 'pause', icon: 'icons/pauseIcon.png' },
		{ id: 'reset', icon: 'icons/resetIcon.png' },
		{ id: 'power', icon: 'icons/powerIcon.png' }
	];
	const settings = { id: 'settings', icon: 'icons/settingsIcon.png' };
	const port1Button = { id: 'port1', icon: 'icons/device-none.png' };
	const port2Button = { id: 'port2', icon: 'icons/device-none.png' };
	const port1Items = [
		{ id: 'empty1', icon: 'icons/device-none.png' },
		{ id: 'mouse1', icon: 'icons/device-mouse.png' },
		{ id: 'keyset11', icon: 'icons/device-keyset-1.png' },
		{ id: 'keyset12', icon: 'icons/device-keyset-2.png' }
	];
	const port2Items = [
		{ id: 'empty2', icon: 'icons/device-none.png' },
		{ id: 'mouse2', icon: 'icons/device-mouse.png' },
		{ id: 'keyset21', icon: 'icons/device-keyset-1.png' },
		{ id: 'keyset22', icon: 'icons/device-keyset-2.png' }
	];
	const shell = { id: 'shell', icon: 'icons/retroShellIcon.png' };
	const monitor = { id: 'monitor', icon: 'icons/monitorIcon.png' };
	const layoutButton = { id: 'layout', icon: 'icons/layoutIcon.png' };
	const layoutItems = [
		{ id: 'aspect', icon: 'icons/layoutAspectIcon.png' },
		{ id: 'fit', icon: 'icons/layoutFitIcon.png' },
		{ id: 'full', icon: 'icons/layoutFullIcon.png' }
	];

	$: {
		switch($port1) {
			case 1: port1Button.icon = 'icons/device-mouse.png'; break;
			case 2: port1Button.icon = 'icons/device-keyset-1.png'; break;
			case 3: port1Button.icon = 'icons/device-keyset-2.png'; break;
			default: port1Button.icon = 'icons/device-none.png'; break;
		}
	}

	$: {
		switch($port2) {
			case 1: port2Button.icon = 'icons/device-mouse.png'; break;
			case 2: port2Button.icon = 'icons/device-keyset-1.png'; break;
			case 3: port2Button.icon = 'icons/device-keyset-2.png'; break;
			default: port2Button.icon = 'icons/device-none.png'; break;
		}
	}

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

<div transition:fade={{ duration }} class="">
	<div class="absolute top-0 left-0 h-full bg-gray-500/40 flex flex-col w-16 items-center z-40">
		<div class="w-10 mt-2 flex flex-col space-y-1">
			<SidebarSection
				on:select={select}
				expanded={sel == 'control'}
				item={control}
				subitems={controlItems}
			/>
			<SidebarButton on:select={select} item={settings} highlighted={$showSettings} />
			<SidebarSection
				on:select={select}
				expanded={sel == 'port1'}
				item={port1Button}
				subitems={port1Items}
			/>
			<SidebarSection
				on:select={select}
				expanded={sel == 'port2'}
				item={port2Button}
				subitems={port2Items}
			/>
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
