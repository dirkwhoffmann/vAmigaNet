<script lang="ts">
	import "../app.css"
	import {onMount} from "svelte"
	import ToolbarItem from '$lib/ToolbarItem.svelte'
	import ToolbarSeperator from '$lib/ToolbarSeparator.svelte'
	import ToolbarSection from '$lib/ToolbarSection.svelte'
	import FaRegClock from 'svelte-icons/fa/FaRegClock.svelte'
	import ToolbarSeparator from "$lib/ToolbarSeparator.svelte";

	/*
	let item1: ToolbarItem = { }; 
	let item2 = ToolBarItem();
	let array = [item1, item2];
	*/
	/*
    let components:ToolbarItem[] = [
        [ToolbarItem { content: 'Initial' }],
        [ToolbarItem { content: 'Initial 2' }],
    ];
	*/

	onMount(() => {

		console.log("onMount");
	})

</script>

<body class="h-screen bg-black text-white">
 
<div class="flex p-4">

	<div class="w-64"></div>

	<ToolbarSection>
		<ToolbarItem iconName="inspectorIcon"/>
		<ToolbarItem iconName="monitorIcon"/>
		<ToolbarItem iconName="retroShellIcon"/>
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection>
		<ToolbarItem iconName="takeSnapshotIcon"/>
		<ToolbarItem iconName="revertSnapshotIcon"/>
		<ToolbarItem iconName="snapshotBrowserIcon"/>
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection>
		<ToolbarItem iconName="takeScreenshotIcon"/>
		<ToolbarItem iconName="screenshotBrowserIcon"/>
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection>
		<ToolbarItem iconName="portIcon"/>
		<ToolbarItem iconName="portIcon"/>
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection>
		<ToolbarItem iconName="keyboardIcon"/>
		<ToolbarItem iconName="settingsIcon"/>
		<ToolbarItem iconName="virtualMachineIcon"/>
	</ToolbarSection>
	<ToolbarSeparator />
	<ToolbarSection>
		<ToolbarItem iconName="pauseIcon"/>
		<ToolbarItem iconName="resetIcon"/>
		<ToolbarItem iconName="powerIcon"/>
	</ToolbarSection>
</div>
<!-- <p>Visit <a href="https://kit.svelte.dev">kit.svelte.dev</a> to read the Svelte documentation</p> -->

</body>
