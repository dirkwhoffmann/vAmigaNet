<script lang="ts">
    import { Layer } from '$lib/types';
    import { amiga, dragItem, dragType, initialized, layer, proxy } from '$lib/stores';

    function handleDragEnter(event: DragEvent)
    {
        event.preventDefault();
        if (!event.dataTransfer) {
            return;
        }
    }

    function handleDragOver(event: DragEvent)
    {
        event.preventDefault();
    }

    function handleDragLeave(event: DragEvent)
    {

    }

    async function handleDragDrop(event: DragEvent)
    {
        event.preventDefault();

        // Only proceed if we've received any data
        if (!event.dataTransfer || !event.dataTransfer.items) return;

        // Only proceed if the user has dragged in a single item
        if (event.dataTransfer.items.length !== 1) return;
        let item = event.dataTransfer.items[0];

        // Only proceed if the user has dragged in a file
        if (item.kind !== 'file') return;
        const file = item.getAsFile();
        if (!file) return;

        // Get the file data
        let blob = await file.arrayBuffer();
        let uint8View = new Uint8Array(blob);

        // Check the file type
        switch ($amiga.getFileType(blob)) {
            case $proxy.FILETYPE_ROM:
                await handleDraggedRom(uint8View);
                return;
            case $proxy.FILETYPE_ADF:
            case $proxy.FILETYPE_EADF:
            case $proxy.FILETYPE_DMS:
            case $proxy.FILETYPE_EXE:
                handleDraggedDisk(uint8View);
                return;
            case $proxy.FILETYPE_HDF:
                handleDraggedHardDrive(uint8View);
                return;
            default:
                console.warn('Unsupported file format');
                return;
        }
    }

    async function handleDraggedRom(blob: Uint8Array)
    {
        $proxy.addRom(blob);
    }

    function handleDraggedDisk(blob: Uint8Array)
    {
        $dragItem = blob;
        $dragType = 'floppy';
        $layer = Layer.dropzone;
    }

    function handleDraggedHardDrive(blob: Uint8Array)
    {
        $dragItem = blob;
        $dragType = 'harddrive';
        $layer = Layer.dropzone;
    }

</script>

<div
        class="h-screen w-screen flex flex-col flex-grow overflow-clip"
        on:dragenter={handleDragEnter}
        on:dragleave={handleDragLeave}
        on:dragover={handleDragOver}
        on:drop={handleDragDrop}
>
    {#if $initialized}
        <slot/>
    {/if}
</div>
