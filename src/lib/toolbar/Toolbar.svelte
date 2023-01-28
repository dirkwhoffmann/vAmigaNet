<script lang="ts">
	import ToolbarItem from '$lib/toolbar/ToolbarItem.svelte';
	import ToolbarSeparator from '$lib/toolbar/ToolbarSeparator.svelte';
	import ToolbarSection from '$lib/toolbar/ToolbarSection.svelte';
	import { createEventDispatcher } from 'svelte';

	/*
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
	*/

	export let bgcolor = 'bg-red-600';
	let tbcolor1 = 'bg-gray-300';
	let tbcolor2 = 'bg-gray-300';
</script>

<div class="{bgcolor} flex w-screen justify-between p-0">
	<!--<ToolbarSeparator />-->
	<ToolbarSection bgcolor={tbcolor2}>
		<!--<ToolbarItem iconName="inspectorIcon" />-->
		<ToolbarItem id="retroShell" iconName="retroShellIcon" on:click />
		<ToolbarItem id="monitor" iconName="monitorIcon" on:click />
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
		<ToolbarItem id="pause" iconName="pauseIcon" on:click />
		<ToolbarItem id="reset" iconName="resetIcon" on:click />
		<ToolbarItem id="power" iconName="powerIcon" on:click />
	</ToolbarSection>
</div>
