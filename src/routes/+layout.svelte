<script lang="ts">
    import { vAmiga } from "$lib/stores";
	import { onMount } from "svelte";

    let ready_to_load_wasm=false;

    onMount(() => {
        console.log('onMount Layout()');
        $vAmiga.onRuntimeInitialized= ()=> {
            console.log("onRuntimeInitialized !") 
        };
        
        /**
         * emscriptens glue code which is located in vAmiga.js looks for the reference in window.Module
         * the emsdk doc says...
         * Module is a global JavaScript object with attributes that Emscripten-generated code calls at various points in its execution.
         * Developers can provide an implementation of Module to control the execution of code. For example, to define how notification messages from Emscripten are displayed, developers implement the Module.print attribute.
         * When an Emscripten application starts up it looks at the values on the Module object and applies them. Note that changing the values after startup will not work in general.
         */
        window.Module = $vAmiga; //so give it the reference to our sveltekit vAmiga store variable
        
        ready_to_load_wasm=true; //now let it load the wasm program
    });

</script>

<svelte:head>
    <script type='text/javascript'>
        calledRun=false;
    </script>
    {#if ready_to_load_wasm}
        <script src="vAmiga.js"></script>        
    {/if}
</svelte:head>
<slot></slot>