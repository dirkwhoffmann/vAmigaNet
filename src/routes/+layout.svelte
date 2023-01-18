<script lang="ts">
    import { vAmiga, enums, amiga, retroShell, MSG_CONSOLE } from "$lib/stores";
	import { onMount } from "svelte";

    let ready_to_load_wasm=false;
    
    onMount(() => {
        console.log('layout+: onMount');
        $vAmiga.onRuntimeInitialized= ()=> {
            console.log("layout+: onRuntimeInitialized");

            console.log('Creating proxies...');
            $enums = new $vAmiga.EnumProxy();
            $amiga = new $vAmiga.AmigaProxy();
            $retroShell = new $vAmiga.RetroShellProxy();
        };
        
        /**
         * vAmiga state dictionary, we can bind ui components to it 
         */
        $vAmiga.state={};
        $vAmiga.state.someMessage = 0;
        $vAmiga.update=0;

        /**
         * incoming Messages
         * @param msg
         */
        $vAmiga.processMsg = function(id: number, d1: number, d2: number, d3: number, d4: number) {
            console.log(`Message: ${$enums.MsgTypeKey(id)}(${d1}, ${d2}, ${d3}, ${d4})`);
            /*
            $vAmiga.state.last_message=message;
            $vAmiga.state[message]=[d1,d2,d3,d4];
            $vAmiga.state["SOME_MESSAGE"] += 1; 
            */
            $MSG_CONSOLE += 1;
        }
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
        <script type='text/javascript'>
        console.log(window.Module);
        </script>

        <script src="vAmiga.js"></script>        
    {/if}
</svelte:head>
<slot></slot>
