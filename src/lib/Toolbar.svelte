<script lang="ts">
	import ToolbarItem from '$lib/ToolbarItem.svelte';
	import ToolbarSeparator from '$lib/ToolbarSeparator.svelte';
	import ToolbarSection from '$lib/ToolbarSection.svelte';
	export let bgcolor = 'bg-red-600';
    let tbcolor1 = "bg-gray-300"
	let tbcolor2 = "bg-gray-300"
</script>

<div class="{bgcolor} flex w-screen p-0">
	<ToolbarSeparator />
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="inspectorIcon" />
		<ToolbarItem iconName="monitorIcon" />
		<ToolbarItem iconName="retroShellIcon" />
	</ToolbarSection>
	<ToolbarSeparator />
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
	<ToolbarSection bgcolor={tbcolor2}>
		<ToolbarItem iconName="pauseIcon" />
		<ToolbarItem iconName="resetIcon" />
		<ToolbarItem iconName="powerIcon" />
	</ToolbarSection>
	<ToolbarSeparator />
</div>
