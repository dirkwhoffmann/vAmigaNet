<script lang="ts">
	import { proxy, amiga, memory, initialized } from '$lib/stores';
	import { db } from '$lib/db/db';

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

		console.log('handleDragDrop');
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

							// Check if this file is an ADF
							try {
								if ($amiga.insertDisk(uint8View, blob.byteLength, 0)) return;
							} catch (exc) {}
							console.log('No valid disk');

							let info = $memory.analyzeRom(uint8View, blob.byteLength);
							console.log('ROM analyzed: ', info);

							if (info.crc32) {
								try {
									const t = info.title;

									const id = await db.roms.add({
										crc32: info.crc32,
										title: info.title,
										version: info.version,
										released: info.released,
										model: info.model,
										isAros: info.isAros,
										isDiag: info.isDiag,
										isCommodore: info.isCommodore,
										isHyperion: info.isHyperion,
										isPatched: info.isPatched,
										isUnknown: info.isUnknown,
										rom: uint8View,
										ext: null,
										extStart: 0
									});

									console.log(`${t} successfully added with id ${id}`);
								} catch (error) {
									console.log(`Failed to add Kickstart`);
								}
							}
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
