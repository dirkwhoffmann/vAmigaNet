<script lang="ts">
	import MyButton from './widgets/MyButton.svelte';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/db/db';
	import { browser } from '$app/environment';
	import FaTrash from 'svelte-icons/fa/FaTrash.svelte';
	import { memory, initialized } from '$lib/stores';

	let roms = liveQuery(() => (browser ? db.roms.toArray() : []));

	let show = true;

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
		try {
			await db.roms.delete(id);
			console.log(`{id} successfully deleted`);
		} catch (error) {
			console.log(`Failed to delete Kickstart`, error);
		}
	}

	const debug = ''; // 'border-2';
</script>

{#if show}
	<div class="absolute top-0 left-0 h-screen w-screen flex justify-center items-center">
		<div
			class="relative w-2/3 flex flex-col py-4 justify-center bg-gray-700 text-gray-300 border-2 border-gray-300 rounded-xl font-josefin"
		>
			<!-- Header -->
			<div class="w-full text-center text-3xl font-semibold text-white">Databas experiments</div>
			<hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />

			<!-- Main -->
			<div class="overflow-x-auto h-96 border-0 overflow-x-hidden overflow-y-auto">
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
												<!-- <div class="opacity-50">CRC {rom.crc32}</div>-->
											</div>
											<div class="{debug} h-full w-4 m-2 flex items-center">
												<button class="w-full" on:click={(e) => deleteAction(e, rom.id)}
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

			<!-- Footer -->
			<hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />
			<div class="w-full flex justify-center">
				<MyButton on:click={close} label="Close" />
			</div>
		</div>
	</div>
{/if}
