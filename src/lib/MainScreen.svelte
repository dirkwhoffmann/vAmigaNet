<script lang="ts">
	import { proxy, amiga, memory, initialized } from '$lib/stores';

	function handleDragEnter(event: DragEvent) {
		event.preventDefault();
		if (!event.dataTransfer) {
			console.log('DragEnter: dataTransfer == null');
			return;
		}
		console.log('DragEnter: ' + event.dataTransfer.items[0]);
	}

	function handleDragOver(event: DragEvent) {
		event.preventDefault();
	}

	function handleDragLeave(event: DragEvent) {
		console.log('DragLeave');
	}

	async function handleDragDrop(event: DragEvent) {
		event.preventDefault();

		if (event.dataTransfer && event.dataTransfer.items) {
			if (event.dataTransfer.items.length == 1) {
				let item = event.dataTransfer.items[0];
				if (item.kind === 'file') {
					const file = item.getAsFile();
					if (file) {
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
	}

	function handleDragStart(event: DragEvent) {
		console.log('DragStart');
	}

	function handleDragEnd(event: DragEvent) {
		console.log('DragEnd');
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
		<slot />
	{/if}
</div>
