<script lang="ts">
	import { vAmiga, amiga, retroShell } from '$lib/stores';
	import { MsgCloseConsole, MsgUpdateConsole } from '$lib/stores';
	import { MsgScriptDone, MsgScriptPause, MsgScriptAbort, MsgScriptWakeup } from '$lib/stores';
	import { onMount } from 'svelte';

	// Console contents
	let value = '';

	let textarea:HTMLTextAreaElement; 

	// Message handlers
	$: {
		$MsgCloseConsole;
		console.log('MsgCloseConsole');
	}
	$: if ($MsgUpdateConsole > 0) {
		let rel = $retroShell.getCursorRel();
		console.log('MsgUpdateConsole rel = ' + rel);
		textarea.value = $retroShell.getText();
		textarea.focus();
		textarea.setSelectionRange(textarea.value.length + rel - 1, textarea.value.length + rel);
		textarea.scrollTop = textarea.scrollHeight;
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
		e.preventDefault();
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
			case 'Enter':
			console.log("Return "  +e.shiftKey);
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
				console.log("Other key: " + e.key);
				$retroShell.pressKey(e.key.charCodeAt(0));
		}
	}
</script>

<textarea bind:this={textarea} readonly class="w-full h-full opacity-50" on:keydown={onKeyDown} />
