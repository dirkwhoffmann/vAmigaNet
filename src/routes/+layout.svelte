<svelte:head>
    <script type='text/javascript'>
        calledRun=false;
        Module = {
            onRuntimeInitialized: function() {
                    console.log("onRuntimeInitialized"); 
            }
        };
    </script>
    <script src="vAmiga.js"></script>
</svelte:head>
<slot></slot>