<script>
    import { vAmiga, amiga, retroShell } from "$lib/stores";
	import { onMount } from "svelte";
    export let text = '';

	let value = '';

    onMount(() => {
        console.log('RetroShell: onMount');
    });

	function onKeyDown(e) {

		switch (e.keyCode) {
            
            case 37: // Left
                $retroShell.pressLeft();
				break;
			case 39: // Right
                $retroShell.pressRight();
				break;
			case 40: // Down
                $retroShell.pressDown();
				break;
			case 38: // Up
                $retroShell.pressUp();
				break;
            
			default:
				console.log("MSG_POWER_OFF: " + $vAmiga.MSG_POWER_OFF);
				console.log("MSG_POWER_ERROR: " + $vAmiga.MSG_POWER_ERROR);
				$retroShell.pressKey(e.keyCode);
				value += e.keyCode;
		}
	}
</script>

<textarea bind:value readonly rows="10" cols="80" on:keydown={onKeyDown} />
