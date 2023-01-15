<svelte:head>
	<script type="text/javascript">
		console.log('Initialize...');
		calledRun = false;
		Module = {
			onRuntimeInitialized: function () {
				console.log('onRuntimeInitialized');
			},
			canvas: (function () {
				return document.getElementById('canvas');
			})()
		};
	</script>
	<script src="vAmiga.js"></script>
</svelte:head>
<slot />
