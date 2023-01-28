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

	export let bgcolor = 'bg-gray-200';
	let tbcolor1 = 'bg-gray-500/50';
	let tbcolor2 = 'transparent';
</script>

<div class="bg-gray-300/50 flex w-screen justify-between p-0">
	<!--<ToolbarSeparator />-->
	<ToolbarSection bgcolor={tbcolor2}>
		<!--<ToolbarItem iconName="inspectorIcon" />-->
		<ToolbarItem id="retroShell" iconName="retroShellIcon" {bgcolor} on:click />
		<ToolbarItem id="monitor" iconName="monitorIcon" {bgcolor} on:click />
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
		<ToolbarItem id="pause" iconName="pauseIcon" {bgcolor} on:click />
		<ToolbarItem id="reset" iconName="resetIcon" {bgcolor} on:click />
		<ToolbarItem id="power" iconName="powerIcon" {bgcolor} on:click />
	</ToolbarSection>
</div>
