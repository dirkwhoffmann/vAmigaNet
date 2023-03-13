<script lang="ts">
    import { amiga, dfConnected, dfHasDisk, dragItem, dragType, hdConnected, layer } from '$lib/stores';
    import { Layer } from '$lib/types';
    import { fade } from 'svelte/transition';
    import DropZoneCell from './DropZoneCell.svelte';

    function insert(drive: number)
    {
        if ($dragItem) {

            // Insert disk
            $amiga.insertDisk($dragItem, drive);

            // Start emulation if necessary
            if (!$amiga.running) $amiga.run();
        }
        $layer = Layer.none;
    }

    function attach(drive: number)
    {
        console.log("HardDrive attach", drive);

        if ($dragItem) {

            // Attach hard drive
            $amiga.attachHardDrive($dragItem, drive);

            // Start emulation if necessary
            if (!$amiga.running) $amiga.run();
        }
        $layer = Layer.none;
    }

</script>

{#if $layer === Layer.dropzone}
    <div class="absolute top-10 left-0 w-screen flex justify-center" transition:fade>
        <div class="relative flex justify-center space-x-4 p-4 rounded-xl items-center">

            {#if $dragType === 'floppy'}
                <DropZoneCell id={0}
                              icon1="icons/disk.png"
                              icon2={$dfHasDisk[0] ? "icons/disk.png" : ""}
                              name="DF0"
                              enabled={$dfConnected[0]}
                              on:drive={() => insert(0)}/>
                <DropZoneCell id={1}
                              icon1="icons/disk.png"
                              icon2={$dfHasDisk[1] ? "icons/disk.png" : ""}
                              name="DF1"
                              enabled={$dfConnected[1]}
                              on:drive={() => insert(1)}/>
                <DropZoneCell id={2}
                              icon1="icons/disk.png"
                              icon2={$dfHasDisk[1] ? "icons/disk.png" : ""}
                              name="DF2"
                              enabled={$dfConnected[2]}
                              on:drive={() => insert(2)}/>
                <DropZoneCell id={3}
                              icon1="icons/disk.png"
                              icon2={$dfHasDisk[1] ? "icons/disk.png" : ""}
                              name="DF3"
                              enabled={$dfConnected[3]}
                              on:drive={() => insert(3)}/>
            {:else}
                <DropZoneCell id={0}
                              icon1="icons/hard-drive.png"
                              icon2="icons/hard-drive.png"
                              name="HD0"
                              enabled={$hdConnected[0]}
                              on:drive={() => attach(0)}/>
                <DropZoneCell id={1}
                              icon1="icons/hard-drive.png"
                              icon2="icons/hard-drive.png"
                              name="HD1"
                              enabled={$hdConnected[1]}
                              on:drive={() => attach(1)}/>
                <DropZoneCell id={2}
                              icon1="icons/hard-drive.png"
                              icon2="icons/hard-drive.png"
                              name="HD2"
                              enabled={$hdConnected[2]}
                              on:drive={() => attach(2)}/>
                <DropZoneCell id={3}
                              icon1="icons/hard-drive.png"
                              icon2="icons/hard-drive.png"
                              name="HD3"
                              enabled={$hdConnected[3]}
                              on:drive={() => attach(3)}/>
            {/if}
        </div>
    </div>
{/if}