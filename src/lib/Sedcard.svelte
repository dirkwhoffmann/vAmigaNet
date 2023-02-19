<script lang="ts">
	import { fade } from 'svelte/transition';
	import IoMdClose from 'svelte-icons/io/IoMdClose.svelte';
	import { proxy, audio, amiga } from '$lib/stores';
    
	export let selected: DataBaseItem | null;
	export let show = true;

	$: src = 'footage/' + (selected?.url ?? '') + '-large.jpg';

	function close() {
		console.log('close');
		show = false;
	}

	async function runTitle() {
        await $audio.setup();
		if (selected) {
			console.log('Running ' + selected.title + '...');
			$amiga.powerOff();
			console.log('Configuring CHIP: ' + selected.memory[0]);
			$amiga.configure($proxy.OPT_CHIP_RAM, selected.memory[0]);
			console.log('Configuring SLOW: ' + selected.memory[1]);
			$amiga.configure($proxy.OPT_SLOW_RAM, selected.memory[1]);
			console.log('Configuring FAST: ' + selected.memory[2]);
			$amiga.configure($proxy.OPT_FAST_RAM, selected.memory[2]);
			for (let i = 0; i < selected.adf.length; i++) {
				console.log('Inserting disk ' + i + ': ' + selected.adf[i]);
				$proxy.insert(selected.adf[i], i);
			}
			$amiga.run();
		}
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
				<button class="btn btn-sm flex p-0 border-2 border-white" on:click={close}
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
			<div class="mt-4 relative">
				<button class="btn" on:click={runTitle}>Start</button>
			</div>
		</div>
	</div>
{/if}
