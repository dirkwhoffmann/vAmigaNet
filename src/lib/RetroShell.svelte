<script lang="ts">
    import { fade } from 'svelte/transition';
    import { Layer } from "$lib/types";
    import {
        layer,
        MsgConsoleClose,
        MsgConsoleUpdate,
        MsgScriptAbort,
        MsgScriptDone,
        MsgScriptPause,
        MsgScriptWakeup,
        retroShell
    } from "$lib/stores";

    // Textual contents of the console window
    let value = '';

    // Bindings
    let textarea: HTMLTextAreaElement | null;

    // Message handlers
    $: if ($MsgConsoleClose) {
        $layer = Layer.none;
    }
    $: if ($MsgConsoleUpdate) {
        let rel = $retroShell.getCursorRel();
        if (textarea) {
            textarea.value = $retroShell.getText();
            textarea.focus();
            textarea.setSelectionRange(textarea.value.length + rel - 1, textarea.value.length + rel);
            textarea.scrollTop = textarea.scrollHeight;
        }
    }
    /*
    $: if ($MsgScriptDone) {
        console.log('MsgScriptDone');
    }
    $: if ($MsgScriptPause) {
        console.log('MsgScriptPause');
    }
    $: if ($MsgScriptAbort) {
        console.log('MsgScriptAbort');
    }
    $: if ($MsgScriptWakeup) {
        console.log('MsgScriptWakeup');
    }
    */

    function onKeyDown(e: KeyboardEvent)
    {
        e.preventDefault();

        if (e.ctrlKey) {
            switch (e.key) {
                case 'k':
                    $retroShell.pressCut();
                    break;

                case 'a':
                    $retroShell.pressHome();
                    break;

                default:
                    break;
            }
            return;
        }

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
            case 'Enter':
                e.shiftKey ? $retroShell.pressShiftReturn() : $retroShell.pressReturn();
                break;
            case 'Tab':
                $retroShell.pressTab();
                break;
            default:
                if (e.key.length == 1) {
                    $retroShell.pressKey(e.key.charCodeAt(0));
                }
        }
    }
</script>

{#if $layer === Layer.shell}
    <div class="absolute top-0 left-0 w-full h-full flex overflow-auto" transition:fade>
        <div class="w-16 mr-1"></div>
        <div class="bg-gray-500/75 grow h-full overflow-auto">
		<textarea
                bind:this={textarea}
                readonly
                style="resize: none; font-variant-ligatures: none"
                class="font-azeret text-base focus:border-transparent focus:outline-none focus:ring-0 text-white bg-transparent w-full h-full p-2"
                on:keydown={onKeyDown}
        ></textarea>
        </div>
    </div>
{/if}