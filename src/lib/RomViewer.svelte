<script lang="ts">
	import MyButton from './widgets/MyButton.svelte';
	import { fade } from 'svelte/transition';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/db/db';
	import { browser } from '$app/environment';
	import FaTrash from 'svelte-icons/fa/FaTrash.svelte';
	import FaWindowClose from 'svelte-icons/fa/FaWindowClose.svelte';
	import IoMdClose from 'svelte-icons/io/IoMdClose.svelte';
	import { proxy, amiga, memory, initialized } from '$lib/stores';

	let roms = liveQuery(() => (browser ? db.roms.orderBy('title').toArray() : []));

	$: console.log("roms = ", $roms); 

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
				console.log(`Failed to add Kickstart`);
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

	function version(rom: RomEntry) {
		if (rom.isUnknown) {
			return 'CRC ' + rom.crc32.toString();
		} else {
			return rom.version;
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
			: 'rom-unknown.png';
	}

	function close() {
		console.log('close');
		show = false;
	}

	async function deleteAction(e: MouseEvent, id: number) {
		console.log('deleteAction: ', id);
		try {
			await db.roms.delete(id);
			console.log(`{id} successfully deleted`);
		} catch (error) {
			console.log(`Failed to delete Kickstart`, error);
		}
	}

	async function installAction(e: MouseEvent, crc: number) {
		console.log('installAction: ', crc);
		$amiga.powerOff();
		await $proxy.installRom(crc);
		$amiga.hardReset();
		$amiga.run();
	}

	const debug = ''; //'border-2';
	let activeTab = 0;
</script>

<div class="{debug} border-green-500 h-full flex flex-col">
	<div class="flex items-center space-x-2 mx-2">
		<div class="{debug} tabs tabs-boxed flex grow">
			<button class="tab" class:tab-active={activeTab == 0} on:click={() => (activeTab = 0)}
				>Installed Roms</button
			>
			<button class="tab" class:tab-active={activeTab == 1} on:click={() => (activeTab = 1)}
				>Legal Information</button
			>
			<div class="flex grow justify-end">
				<button class="btn btn-sm btn-primary flex w-8 p-0" on:click={close}><IoMdClose /></button>
			</div>
		</div>
	</div>
	<div class="h-96 mt-4 overflow-auto {debug} p-1 text-base-content">
		{#if activeTab == 0}
			<table in:fade class="table table-compact table-zebra w-full">
				<tbody class={debug}>
					<tr class="h-8 {debug} text-center text-base-content border-purple-400 font-josefin">
						Use drag-and-drop to add additional ROM images.
					</tr>
					{#if $roms}
						{#each $roms as rom}
							<tr class="h-8 {debug} border-purple-400">
								<td class="">
									<div class="flex h-[5.5rem] space-x-4">
										<div class="{debug} h-full w-[4.5rem]">
											<img
												class="h-full w-full"
												src={'icons/' + imageUrl(rom)}
												alt="Rom Chip Icon"
											/>
										</div>
										<div class="{debug} h-full flex flex-col grow overflow-hidden">
											<div class="font-bold">{rom.title}</div>
											<div class="opacity-60">{version(rom)}</div>
											<div class="opacity-60">{rom.model}</div>
										</div>
										<div class="{debug} h-full flex items-center">
											<button
												class="btn btn-primary btn-outline btn-sm"
												on:click={(e) => installAction(e, rom.crc32)}>Install</button
											>
										</div>
										<div class="{debug} h-full flex items-center">
											<button
												class="btn btn-primary btn-outline btn-sm w-8 p-1.5"
												on:click={(e) => deleteAction(e, rom.crc32)}><FaTrash /></button
											>
										</div>
									</div>
								</td>
							</tr>
						{/each}
					{/if}
				</tbody>
			</table>
		{:else}
			<article in:fade class="mx-1 prose {debug}">
				<h3>Kickstart</h3>
				<p>
					To run the emulator, a Kickstart ROM is required. The original Amiga ROMs are the
					intellectual property of Cloanto™ and cannot be freely distributed. If you own a legal
					Kickstart ROM, you can add the ROM image to vAmiga Online by drag & drop. When a supported
					image is detected, it becomes accessible in the ROM database. The ROMs are kept in the
					browser's memory and will be available during the next browser session.
				</p>
				<h3>Encrypted ROMs</h3>
				<p>
					If you have purchased an older version of Amiga Forever™, you may be in possession of
					encrypted ROM files. These files come with a .key file that is needed to decrypt the ROM.
					Encrypted ROMs are not yet supported by the emulator. They must be decrypted manually
					before they can be used within vAmiga Online.
				</p>
				<h3>AROS</h3>
				<p>
					If you don't have the original Kickstart at hand, you may install the Amiga Research
					Operating System ROM (AROS). AROS is an open source Kickstart variant, which can be freely
					redistributed. Unfortunately not all Amiga programs are compatible with AROS, which is why
					I strongly recommend to use original ROMs. 					
				</p>
			</article>
		{/if}
	</div>
</div>
