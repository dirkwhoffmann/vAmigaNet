<script lang="ts">
	import type { DataBaseItem } from '$lib/types';
	import { fade } from 'svelte/transition';
	import IoMdClose from 'svelte-icons/io/IoMdClose.svelte';
	import { proxy, kickstarts } from '$lib/stores';

	export let selected: DataBaseItem | null;
	export let show = true;

	$: src = 'footage/' + (selected?.url ?? '') + '-large.jpg';

	$: enabled = $kickstarts.map(kick => kick.crc32).some(crc => selected?.roms.includes(crc));
	$: disabled = !enabled; 

	function close() {
		show = false;
	}

	async function runTitle() {
		$proxy.runShowcase(selected);
	}
</script>

{#if selected}
	<div class="" in:fade>
		<!-- Background -->
		<div class="absolute top-0 left-0 px-0 py-0 w-full h-full">
			<img class="brightness-90 blur-[2px]" {src} alt="Bg" />
		</div>
		<div class="absolute top-0 left-0 px-0 py-0 w-full h-full">
			<img class="" src="footage/blank-large.png" alt="Alt" />
		</div>
		<!-- Description -->
		<div class="relative border-0">
			<div class="absolute top-0 right-0">
				<button class="btn btn-sm btn-square flex p-0 border-2 border-white" on:click={close}
					><IoMdClose /></button
				>
			</div>
			<div class="">
				<div class="font-sofia-extra text-8xl">{selected.title}</div>
				<div class="flex pb-10 items-center">
					<div class="text-xs p-0.5 mr-2 border-2 h-fit rounded-md font-azaret">PAL</div>
					<div class="font-sofia-semi text-2xl flex">{selected.subtitle}</div>
				</div>
				<div class="flex font-josefin text-lg w-2/3 pb-5">{selected.description}</div>
			</div>
			{#if disabled}
				<div class="text-error font-josefin">
					Please install Kickstart 1.2 or Kickstart 1.3 to unlock this title.
				</div>
				<div class="mt-4 relative">
					<button class="btn btn-disabled bg-gray-500 text-white opacity-20" on:click={runTitle}
						>Start</button
					>
				</div>
			{:else}
				<div class="mt-4 relative">
					<button class="btn btn-primary" on:click={runTitle}>Start</button>
				</div>
			{/if}
		</div>
	</div>
{/if}
