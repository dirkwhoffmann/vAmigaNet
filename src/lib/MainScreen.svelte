<script lang="ts">
	import { proxy, amiga, memory, initialized } from '$lib/stores';

	function handleDragEnter(e) {
		e.preventDefault();
		console.log('DragEnter: ' + e.dataTransfer.items[0]);
	}

	function handleDragOver(event) {
		event.preventDefault();
	}

	function handleDragLeave(e) {
		console.log('DragLeave: ');
	}

	async function handleDragDrop(event) {
		event.preventDefault();

		if (event.dataTransfer.items) {
            if (event.dataTransfer.items.length == 1) {
                let item = event.dataTransfer.items[0];
				if (item.kind === 'file') {
					const file = item.getAsFile();
					console.log(`name = ${file.name}`);
					try {
						let blob = await file.arrayBuffer();
						let uint8View = new Uint8Array(blob);
						console.log('Calling $amiga.insertDisk');
						$amiga.insertDisk(uint8View, blob.byteLength, 0);
					} catch (exc) {
						$proxy.reportException();
					}
				}
			}
		}
	}

	function handleDragStart(e) {
		console.log('DragStart: ');
	}

	function handleDragEnd(e) {
		console.log('DragEnd: ');
	}
</script>

<div class="h-screen w-screen border-2 border-yellow-200 flex flex-col flex-grow overflow-clip" 
	on:dragenter={handleDragEnter}
	on:dragleave={handleDragLeave}
	on:dragover={handleDragOver}
	on:drop={handleDragDrop}
>
{#if $initialized}
	<slot />
{/if}
</div>
