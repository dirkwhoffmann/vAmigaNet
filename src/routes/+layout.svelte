<svelte:head>
	<script type='text/javascript'>
		console.log("do the module thing ");
		calledRun=false;
		Module = {
			onRuntimeInitialized: function() {
				  console.log("onRuntimeInitialized"); 
			},
			canvas: (function() { return document.getElementById('canvas'); })()
		};
	</script>
	<script src="vAmiga.js"></script>
</svelte:head>
<slot></slot>