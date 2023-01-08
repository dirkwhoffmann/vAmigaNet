<script lang="ts">
	import '../app.css';
	import { onMount } from 'svelte';
	import ToolbarItem from '$lib/ToolbarItem.svelte';
	import ToolbarSeperator from '$lib/ToolbarSeparator.svelte';
	import ToolbarSection from '$lib/ToolbarSection.svelte';
	import FaRegClock from 'svelte-icons/fa/FaRegClock.svelte';
	import ToolbarSeparator from '$lib/ToolbarSeparator.svelte';
	import Toolbar from '$lib/Toolbar.svelte';

	let tbcolor1 = "bg-gray-300"
	let tbcolor2 = "bg-gray-300"

	onMount(() => {
		console.log('onMount');
	});
</script>

<body class="h-screen bg-black text-white">
	<Toolbar  bgcolor={tbcolor1} >
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
	</Toolbar>
</body>
