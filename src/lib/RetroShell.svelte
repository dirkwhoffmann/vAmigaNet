<script>
    import { proxy, retroShell } from "$lib/stores";
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
				console.log("hasRom: " + $proxy.hasRom);
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
				value += e.keyCode;
		}
	}
</script>

<textarea bind:value readonly rows="10" cols="80" on:keydown={onKeyDown} />
