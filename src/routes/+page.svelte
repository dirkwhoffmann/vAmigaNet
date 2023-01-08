<script lang="ts">
	import "../app.css"
	import {onMount} from "svelte"
	import ToolbarItem from '$lib/ToolbarItem.svelte'
	import ToolbarSection from '$lib/ToolbarSection.svelte'
	import FaRegClock from 'svelte-icons/fa/FaRegClock.svelte'

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

	<ToolbarSection items=[]/>

	<ToolbarItem iconName="inspectorIcon"/>
	<ToolbarItem iconName="monitorIcon"/>
	<ToolbarItem iconName="retroShellIcon"/>

	<div class="w-64"></div>

	<ToolbarItem iconName="takeSnapshotIcon"/>
	<ToolbarItem iconName="revertSnapshotIcon"/>
	<ToolbarItem iconName="snapshotBrowserIcon"/>

	<div class="w-64"></div>

	<ToolbarItem iconName="takeScreenshotIcon"/>
	<ToolbarItem iconName="screenshotBrowserIcon"/>

	<div class="w-64"></div>

	<ToolbarItem iconName="portIcon"/>
	<ToolbarItem iconName="portIcon"/>

	<div class="w-64"></div>

	<ToolbarItem iconName="keyboardIcon"/>

	<div class="w-64"></div>

	<ToolbarItem iconName="settingsIcon"/>
	<ToolbarItem iconName="virtualMachineIcon"/>

	<div class="w-64"></div>

	<ToolbarItem iconName="pauseIcon"/>
	<ToolbarItem iconName="resetIcon"/>
	<ToolbarItem iconName="powerIcon"/>

	<div class="w-64"></div>
</div>
<!-- <p>Visit <a href="https://kit.svelte.dev">kit.svelte.dev</a> to read the Svelte documentation</p> -->

</body>
