<script lang="ts">
	import MyButton from './widgets/MyButton.svelte';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/db/db';
	import { browser } from '$app/environment';
	import FaTrash from 'svelte-icons/fa/FaTrash.svelte';
	import { memory, initialized } from '$lib/stores';

	let roms = liveQuery(() => (browser ? db.roms.toArray() : []));

	export let show = true;

	async function addRomToDatabase(rom: Uint8Array, ext: Uint8Array | null = null, extStart = 0) {
		console.log('addRomToDatabase: Adding buffer of size ', rom.length);
		let info = $memory.analyzeRom(rom, rom.length);
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
					rom: rom,
					ext: ext,
					extStart: extStart
				});
				console.log(`${t} successfully added with id ${id}`);
			} catch (error) {
				console.log(`Failed to add Kickstart`, error);
			}
		}
	}

	async function installDefaultRoms() {
		console.log('installDefaultRoms');

		try {
			// Add AROS
			let response = await fetch('roms/aros-svn55696-rom.bin');
			let blob = await response.arrayBuffer();
			let arosRom = new Uint8Array(blob);
			response = await fetch('roms/aros-svn55696-ext.bin');
			blob = await response.arrayBuffer();
			let arosExt = new Uint8Array(blob);

			addRomToDatabase(arosRom, arosExt);

			// Add DiagROM
			response = await fetch('roms/diagrom-121.bin');
			blob = await response.arrayBuffer();
			let diagRom = new Uint8Array(blob);

			addRomToDatabase(diagRom);
		} catch (exc) {
			console.error('Cannot install default Roms');
		}
	}

	$: if ($initialized) {
		installDefaultRoms();
	}

	function imageUrl(rom: RomEntry) {
		return rom.isHyperion
			? 'rom-hyperion.png'
			: rom.isAros
			? 'rom-aros.png'
			: rom.isDiag
			? 'rom-diag.png'
			: rom.isCommodore
			? 'rom-commodore.png'
			: ' rom-unknown.png';
	}

	function close() {
		console.log('close');
		show = false;
	}

	async function deleteAction(e: MouseEvent, id: number) {
        console.log("deleteAction: ", id);
        try {
			await db.roms.delete(id);
			console.log(`{id} successfully deleted`);
		} catch (error) {
			console.log(`Failed to delete Kickstart`, error);
		}
	}

	const debug =''; // 'border-2';
</script>

<div class="{debug} flex flex-col h-96">
	<div class="drawer drawer-end {debug} h-full">
		<input id="my-drawer" type="checkbox" class="drawer-toggle" />
		<div class="drawer-content">
			<!-- Page content here -->
            <article class="prose">
            <h3>Kickstart ROMs</h3>
			<p>
				To run the emulator, a Kickstart ROM is required. The original Amiga ROMs are the
				intellectual property of Cloanto and must be provided by the user. If you are in possession
				of a legal Kickstart ROM, you can add the ROM image via drag and drop. Once a ROM image has
				been dragged in and is recognized by the emulator, it will become available in the Machine
				settings.
			</p>
            <h3>AROS</h3>
			<p>
				If you don’t have an original Kickstart at hand, you may choose to install the AROS ROM. The
				Amiga Research Operating System ROM is an open-source Kickstart variant which is freely
				redistributable. Unfortunately, not all Amiga programs are compatible with AROS, which is
				why I strongly recommend using original ROMs.
			</p>
            </article>
		</div>
		<div class="drawer-side">
			<label for="my-drawer" class="drawer-overlay" />

			<table class="table table-compact table-zebra w-full">
				<tbody class={debug}>
					{#if $roms}
						{#each $roms as rom}
							<tr class="border-0">
								<td>
									<div class="flex h-[5.5rem] p-1">
										<div class="{debug} h-full w-[4rem] m-2">
											<img
												class="h-full w-full"
												src={'icons/' + imageUrl(rom)}
												alt="Rom Chip Icon"
											/>
										</div>
										<div class="{debug} h-full m-2 flex flex-col grow overflow-hidden">
											<div class="font-bold text-base">{rom.title}</div>
											<div class="opacity-50">{rom.version}</div>
											<div class="opacity-50">{rom.model}</div>
										</div>
										<div class="{debug} h-full w-4 m-2 flex items-center">
											<button class="w-full" on:click={(e) => deleteAction(e, rom.crc32)}
												><FaTrash /></button
											>
										</div>
									</div>
								</td>
							</tr>
						{/each}
					{/if}
				</tbody>
			</table>
		</div>
	</div>
</div>
<div class="w-full flex justify-between mt-6">
	<label for="my-drawer" class="btn btn-primary drawer-button w-32">Library...</label>
	<button class="btn btn-primary w-32" on:click={close}>Close</button>
</div>
