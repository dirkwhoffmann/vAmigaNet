<script lang="ts">
	import { proxy, amiga, memory } from '$lib/stores';

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

		console.log("handleDragDrop");
		if (event.dataTransfer.items) {
            if (event.dataTransfer.items.length == 1) {
                let item = event.dataTransfer.items[0];
				if (item.kind === 'file') {
					const file = item.getAsFile();
					console.log(`name = ${file.name}`);
					try {
						let blob = await file.arrayBuffer();
						let uint8View = new Uint8Array(blob);
						/*
						console.log('Calling $amiga.insertDisk');
						$amiga.insertDisk(uint8View, blob.byteLength, 0);
						*/
						let info = $memory.analyzeRom(uint8View, blob.byteLength);
						console.log("ROM analyzed");
						console.log("info = ", info);
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

<div class="h-full w-full"
	on:dragenter={handleDragEnter}
	on:dragleave={handleDragLeave}
	on:dragover={handleDragOver}
	on:drop={handleDragDrop}
>
	<slot />
</div>
