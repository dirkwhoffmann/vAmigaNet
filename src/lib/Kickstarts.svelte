<script lang="ts">
	import MyButton from './widgets/MyButton.svelte';
	import { liveQuery } from 'dexie';
	import { db } from '$lib/db/db';
	import { browser } from '$app/environment';
	import FaTrash from 'svelte-icons/fa/FaTrash.svelte';

	let roms = liveQuery(() => (browser ? db.roms.toArray() : []));

	let show = true;

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
			<div class="overflow-x-auto h-96 border-2 overflow-auto">
				<table class="table table-compact table-zebra w-full">
					<tbody class="border-2">
						{#if $roms}
							{#each $roms as rom (rom.id)}
								<tr>
									<td>
										<div class="flex items-center space-x-3">
											<div class="object-scale-down">
												<img
													class="rotate-90 h-24 object-scale-down px-2"
													src="icons/rom-commodore.png"
													alt="Rom Chip Icon"
												/>
											</div>
											<div>
												<div class="font-bold text-xl">{rom.title} {rom.version} ({rom.model})</div>
												<div class="opacity-50">CRC {rom.crc}</div>
											</div>
										</div>
									</td>
									<td>
										<button class="h-6 w-6 mx-2" on:click={(e) => deleteAction(e, rom.id)}
											><FaTrash /></button
										>
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
