<script lang="ts">
	import ToolbarItem from '$lib/toolbar/ToolbarItem.svelte';
	import ToolbarSeparator from '$lib/toolbar/ToolbarSeparator.svelte';
	import ToolbarSection from '$lib/toolbar/ToolbarSection.svelte';
	import { showShell } from '$lib/stores';
	import { createEventDispatcher } from 'svelte';

	import {
		proxy,
		enums,
		amiga,
		retroShell,
		MsgPowerOn,
		MsgPowerOff,
		MsgRun,
		MsgPause,
		MsgHalt
	} from '$lib/stores';

	const dispatch = createEventDispatcher();

	export let bgcolor = 'bg-red-600';
	let tbcolor1 = 'bg-gray-300';
	let tbcolor2 = 'bg-gray-300';

	//
	// Click handlers
	//

	function goBack() {
		console.log('goBack()');
		goto('/');
	}

	function buttonClicked(e: Event) {
		console.log('buttonClicked e = ' + e);
		console.log('target = ' + e.target);
		console.log('id = ' + e.target.id);
	}

	function shellButtonClicked() {
		console.log('shellButtonClicked');
		dispatch('shellButtonClicked');
		// $showShell = !$showShell;
	}

	function monitorButtonClicked() {
		console.log('monitorButtonClicked');
		dispatch('monitorButtonClicked');

		/*
		if (textureRect.x2.target == 1.0) {
			textureRect.zoomIn();
			$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 0);
		} else {
			textureRect.zoomOut();
			$amiga.configure($proxy.OPT_DMA_DEBUG_ENABLE, 1);
		}
		*/
	}

	function pauseButtonClicked() {
		console.log('pauseButtonClicked');
		dispatch('pauseButtonClicked');
	}

	function resetButtonClicked() {
		console.log('resetButtonClicked');
		dispatch('resetButtonClicked');
	}

	function powerButtonClicked() {
		console.log('powertButtonClicked');
		dispatch('powertButtonClicked');
	}
</script>

<div class="{bgcolor} flex w-screen justify-between p-0">
	<!--<ToolbarSeparator />-->
	<ToolbarSection bgcolor={tbcolor2}>
		<!--<ToolbarItem iconName="inspectorIcon" />-->
		<ToolbarItem id="retroShell" iconName="retroShellIcon" on:click={buttonClicked} />
		<ToolbarItem iconName="monitorIcon" on:click={monitorButtonClicked} />
	</ToolbarSection>
	<!-- <ToolbarSeparator />-->
	<!--
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="takeSnapshotIcon" />
		<ToolbarItem iconName="revertSnapshotIcon" />
		<ToolbarItem iconName="snapshotBrowserIcon" />
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="takeScreenshotIcon" />
		<ToolbarItem iconName="screenshotBrowserIcon" />
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="portIcon" />
		<ToolbarItem iconName="portIcon" />
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="keyboardIcon" />
		<ToolbarItem iconName="settingsIcon" />
		<ToolbarItem iconName="virtualMachineIcon" />
	</ToolbarSection>
	<ToolbarSeparator />
	-->
	<ToolbarSeparator />
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="pauseIcon" on:click={pauseButtonClicked} />
		<ToolbarItem iconName="resetIcon" on:click={resetButtonClicked} />
		<ToolbarItem iconName="powerIcon" on:click={powerButtonClicked} />
	</ToolbarSection>
</div>
