<script lang="ts">
	import { Layer } from '$lib/types';
	import { proxy, amiga, memory, initialized, dragItem, layer } from '$lib/stores';
	import { db } from '$lib/Db/db';

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

						let blob = await file.arrayBuffer();
						let uint8View = new Uint8Array(blob);

						switch ($amiga.getFileType(blob)) {
							case $proxy.FILETYPE_ADF:
							case $proxy.FILETYPE_DMS:
							case $proxy.FILETYPE_EXE:
								handleDraggedDisk(uint8View);
								return;
							case $proxy.FILETYPE_ROM:
								await handleDraggedRom(uint8View);
								return;
							default:
								console.warn('Unsupported file format');
								return;
						}
					}
				}
			}
		}
	}

	function handleDraggedDisk(blob: Uint8Array) {
		console.log('Got disk');
		$dragItem = blob;
		$layer = Layer.dropzone;
	}

	async function handleDraggedRom(blob: Uint8Array) {

		$proxy.addRom(blob);
		/*
		let info = $memory.analyzeRom(blob, blob.byteLength);
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
					rom: blob,
					ext: null,
					extStart: 0
				});

				console.log(`${t} successfully added with id ${id}`);
			} catch (error) {
				console.log(`Failed to add Kickstart`);
			}
			console.log("Opening Kickstart viewer");
			$layer = Layer.kickstart;
		}
		*/
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
