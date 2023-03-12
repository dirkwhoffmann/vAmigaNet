<script lang="ts">
    import { createEventDispatcher } from 'svelte';
    import FloppyDriveInfo from '$lib/Statusbar/FloppyDriveInfo.svelte';
    import HardDriveInfo from '$lib/Statusbar/HardDriveInfo.svelte';
    import Speedometer from '$lib/Statusbar/Speedometer.svelte';
    import BarBox from '$lib/Statusbar/BarBox.svelte';
    import {
        amiga,
        audio,
        dfConnected,
        dfCylinder,
        dfHasDisk,
        dfMotor,
        dfProtected,
        dfUnsaved,
        dfWriting,
        halted,
        hdConnected,
        hdCylinder,
        hdReading,
        hdUnsaved,
        hdWriting,
        muted,
        track,
        warp
    } from '$lib/stores';
    import StatusIcon from './StatusIcon.svelte';
    import WarpControl from './WarpControl.svelte';
    import FileDialog from '$lib/Utils/FileDialog.svelte';

    // Bindings
    let speedometer: Speedometer;
    let fdialog: FileDialog;

    $: muteIcon = $muted || $warp;
    $: debugIcon = $track;
    $: haltIcon = $halted;

    const dispatch = createEventDispatcher<{ push: { sender: string } }>();
    const bg = 'bg-gradient-to-t from-primary to-primary/80';

    export function update(animationFrame: number, now: DOMHighResTimeStamp)
    {
        if (speedometer) {
            speedometer.update(animationFrame, now);
        }
    }

    function toggleSidebar(e: Event)
    {
        e.preventDefault();
        $audio.setup();
        dispatch('push', {sender: (e.target as HTMLElement).id});
    }

    function dfMenuAction(df: number, tag: number)
    {
        switch (tag) {
            case 0:
                fdialog.open().then(
                    function (value) {
                        console.log('Inserting disk', value);
                        $amiga.insertDisk(value, df);
                    },
                    function (error) {
                        console.log('error', error);
                    }
                );
                break;
            case 1:
                $amiga.ejectDisk(df);
                break;
            default:
                console.warn("Invalid menu item", tag);
        }
    }

    function hdMenuAction(df: number, tag: number)
    {
        switch (tag) {
            case 0:
                fdialog.open().then(
                    function (value) {
                        console.log('Attaching hard drive', value);
                        $amiga.attachHardDrive(value, df);
                    },
                    function (error) {
                        console.log('error', error);
                    }
                );
                break;
            default:
                console.warn("Invalid menu item", tag);
        }
    }

</script>

<FileDialog bind:this={fdialog}></FileDialog>

<div class="z-50 relative flex h-8 mb-1 {bg}">
    <BarBox>
        <button
                type="button"
                class="flex w-16 h-full justify-center"
                id="vamigaButton"
                on:click={toggleSidebar}
        >
            <img class="h-full" src="icons/vamigaIcon.png" alt="vAmiga Icon"/>
        </button>
    </BarBox>
    <div class="border-0 border-red-500 flex grow">
        {#each Array(4) as _, i}
            {#if $dfConnected[i]}
                <FloppyDriveInfo
                        disk={$dfHasDisk[i]}
                        cyl={$dfCylinder[i]}
                        motor={$dfMotor[i]}
                        writing={$dfWriting[i]}
                        unsaved={$dfUnsaved[i]}
                        wp={$dfProtected[i]}
                        on:select={(e) => { dfMenuAction(i, e.detail.value) }}
                />
            {/if}
        {/each}
        {#each Array(4) as _, i}
            {#if $hdConnected[i]}
                <HardDriveInfo
                        cyl={$hdCylinder[i]}
                        reading={$hdReading[i]}
                        writing={$hdWriting[i]}
                        unsaved={$hdUnsaved[i]}
                        on:select={(e) => { hdMenuAction(i, e.detail.value) }}
                />
            {/if}
        {/each}
    </div>
    {#if haltIcon}
        <StatusIcon src="icons/halt.png"/>
    {/if}
    {#if debugIcon}
        <StatusIcon src="icons/debug.png"/>
    {/if}
    {#if muteIcon}
        <StatusIcon src="icons/mute.png"/>
    {/if}
    <WarpControl/>
    <Speedometer bind:this={speedometer}/>
</div>
