<script>
    import { proxy } from "$lib/stores";
	import { onMount } from "svelte";
    export let text = '';

	let value = '';

    onMount(() => {
        console.log('RetroShell: onMount');
    });

	function onKeyDown(e) {

		switch (e.keyCode) {
            
            case 37: // Left
                $proxy.pressLeft();
				break;
			case 39: // Right
                $proxy.pressRight();
				break;
			case 40: // Down
                $proxy.pressDown();
				break;
			case 38: // Up
                $proxy.pressUp();
				break;
            
			default:
				value += e.keyCode;
		}
	}
</script>

<textarea bind:value readonly rows="10" cols="80" on:keydown={onKeyDown} />
