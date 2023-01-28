<script lang="ts">
	import ToolbarItem from '$lib/toolbar/ToolbarItem.svelte';
	import ToolbarSeparator from '$lib/toolbar/ToolbarSeparator.svelte';
	import ToolbarSection from '$lib/toolbar/ToolbarSection.svelte';
	import { fade } from 'svelte/transition';

	export let bgcolor = 'bg-gray-300';
	let tbcolor1 = 'bg-gray-500/50';
	let tbcolor2 = 'transparent';
	let show = true;

	export function showToolbar() {
		console.log('show');
		show = true;
	}

	export function hideToolbar() {
		console.log('hide');
		show = false;
	}
</script>

{#if show}
	<div
		class="bg-gray-500/80 flex w-screen justify-between p-0"
		transition:fade={{ duration: 500 }}
	>
		<!--<ToolbarSeparator />-->
		<ToolbarSection bgcolor={tbcolor2}>
			<ToolbarItem id="home" icon="icons/homeIcon.png" {bgcolor} on:click />
			<!--<ToolbarItem iconName="inspectorIcon" />-->
			<ToolbarItem id="retroShell" icon="icons/retroShellIcon.png" {bgcolor} on:click />
			<ToolbarItem id="monitor" icon="icons/monitorIcon.png" {bgcolor} on:click />
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
			<ToolbarItem id="pause" icon="icons/pauseIcon.png" {bgcolor} on:click />
			<ToolbarItem id="reset" icon="icons/resetIcon.png" {bgcolor} on:click />
			<ToolbarItem id="power" icon="icons/powerIcon.png" {bgcolor} on:click />
		</ToolbarSection>
	</div>
{/if}
