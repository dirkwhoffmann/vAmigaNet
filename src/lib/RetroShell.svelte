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
            
			case 38:
                $retroShell.pressUp();
				break;
			case 40:
                $retroShell.pressDown();
				break;
            case 37:
                $retroShell.pressLeft();
				break;
			case 39:
                $retroShell.pressRight();
				break;
			case 36:
				$retroShell.pressHome();
				break;
			case 35:
				$retroShell.pressEnd();
				break;
			case 8:
				$retroShell.pressBackspace();
				break;
			case 46:
				$retroShell.pressDelete();
				break;
			/*
			case ???:
                $retroShell.pressCut();
				break;
			*/
			case 13:
				$retroShell.pressReturn();
				break;
			case 9:
				$retroShell.pressTab();
				break;
			/*
			case ???:
                $retroShell.pressShiftReturn();
				break;
			*/
            
			default:
				$retroShell.pressKey(e.keyCode);
				value += e.keyCode;
		}
	}
</script>

<textarea bind:value readonly rows="10" cols="80" on:keydown={onKeyDown} />
