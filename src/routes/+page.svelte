<script lang="ts">
	import "../app.css"
	import Button from '$lib/Button.svelte'
	import FaRegClock from 'svelte-icons/fa/FaRegClock.svelte'
</script>

<body class="h-screen bg-black">

<div class="flex space-x-12">
		<div>a</div>
		<div>a</div>
		<div>a</div>
</div>
<div>
	<Button iconName="inspectorIcon"/>
	<Button iconName="monitorIcon"/>
	<Button iconName="retroShellIcon"/>
	&nbsp;&nbsp;&nbsp;&nbsp;

	<Button iconName="takeSnapshotIcon"/>
	<Button iconName="revertSnapshotIcon"/>
	<Button iconName="snapshotBrowserIcon"/>
	&nbsp;&nbsp;&nbsp;&nbsp;

	<Button iconName="takeScreenshotIcon"/>
	<Button iconName="screenshotBrowserIcon"/>
	&nbsp;&nbsp;&nbsp;&nbsp;

	<Button iconName="portIcon"/>
	<Button iconName="portIcon"/>
	&nbsp;&nbsp;&nbsp;&nbsp;

	<Button iconName="keyboardIcon"/>
	&nbsp;&nbsp;&nbsp;&nbsp;

	<Button iconName="settingsIcon"/>
	<Button iconName="virtualMachineIcon"/>
	&nbsp;&nbsp;&nbsp;&nbsp;

	<Button iconName="pauseIcon"/>
	<Button iconName="resetIcon"/>
	<Button iconName="powerIcon"/>
</div>
<!-- <p>Visit <a href="https://kit.svelte.dev">kit.svelte.dev</a> to read the Svelte documentation</p> -->

</body>
