<script lang="ts">
	import { vAmiga, amiga, retroShell } from '$lib/stores';
	import { MsgCloseConsole, MsgUpdateConsole } from '$lib/stores';
	import { MsgScriptDone, MsgScriptPause, MsgScriptAbort, MsgScriptWakeup } from '$lib/stores';
	import { onMount } from 'svelte';
	export let text = '';

	let value = '';

	// Message handlers
	$: {
		$MsgCloseConsole;
		console.log('MsgCloseConsole');
	}
	$: {
		$MsgUpdateConsole;
		console.log('MsgUpdateConsole');
	}
	$: {
		$MsgScriptDone;
		console.log('MsgScriptDone');
	}
	$: {
		$MsgScriptPause;
		console.log('MsgScriptPause');
	}
	$: {
		$MsgScriptAbort;
		console.log('MsgScriptAbort');
	}
	$: {
		$MsgScriptWakeup;
		console.log('MsgScriptWakeup');
	}

	onMount(() => {
		console.log('RetroShell: onMount');
	});

	function onKeyDown(e: KeyboardEvent) {
		switch (e.key) {
			case 'ArrowUp':
				$retroShell.pressUp();
				break;
			case 'ArrowDown':
				$retroShell.pressDown();
				break;
			case 'ArrowLeft':
				$retroShell.pressLeft();
				break;
			case 'ArrowRight':
				$retroShell.pressRight();
				break;
			case 'Home':
				$retroShell.pressHome();
				break;
			case 'End':
				$retroShell.pressEnd();
				break;
			case 'Backspace':
				$retroShell.pressBackspace();
				break;
			case 'Delete':
				$retroShell.pressDelete();
				break;
			/*
			case ???:
                $retroShell.pressCut();
				break;
			*/
			case 'Return':
				e.shiftKey ? $retroShell.pressShiftReturn() : $retroShell.pressReturn();
				break;
			case 'Tab':
				$retroShell.pressTab();
				break;
			/*
			case ???:
                $retroShell.pressShiftReturn();
				break;
			*/

			default:
				$retroShell.pressKey(e.key);
				value += ' ' + $MsgUpdateConsole;
		}
	}
</script>

<textarea bind:value readonly rows="10" cols="80" on:keydown={onKeyDown} />
