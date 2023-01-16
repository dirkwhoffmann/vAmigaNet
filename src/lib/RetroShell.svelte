<script>
    import { vAmiga } from "$lib/stores";
	import { onMount } from "svelte";
    export let text = '';

	let value = '';

    onMount(() => {
        console.log('RetroShell: onMount');
    });

	function onKeyDown(e) {
		switch (e.keyCode) {
            
            case 37: // Left
				console.log('left');
                rs_pressLeft();
				break;
			case 39: // Right
				console.log('right');
				break;
			case 40: // Down
				console.log('down');
				break;
			case 38: // Up
				console.log('up');
				break;
            
			default:
				value += e.keyCode;
		}
	}
</script>

<textarea bind:value readonly rows="10" cols="80" on:keydown={onKeyDown} />
