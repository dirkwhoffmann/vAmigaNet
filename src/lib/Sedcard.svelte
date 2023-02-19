<script lang="ts">
	import { fade } from 'svelte/transition';

	export let selected: DataBaseItem | null;
	export let show = true;

	$: src = 'footage/' + (selected?.url ?? '') + '-large.jpg';

	function close() {
		console.log('close');
		show = false;
	}

	function runTitle() {
		console.log('runTitle');
	}
</script>

{#if selected}
	<div class="" in:fade>
		<div class="absolute top-0 left-0 p-8 w-full h-full">
			<img class="brightness-90 blur-[2px]" {src} alt="Bg" />
		</div>
		<div class="absolute top-0 left-0 p-8 w-full h-full">
			<img class="" src="footage/blank-large.png" alt="Alt" />
		</div>
		<div class="relative">
			<div class="px-6">
				<div class="font-sofia-extra text-8xl">{selected.title}</div>
				<div class="flex pb-10 items-center">
					<div class="text-xs p-0.5 mr-2 border-2 h-fit rounded-md font-azaret">PAL</div>
					<div class="font-sofia-semi text-2xl flex">{selected.subtitle}</div>
				</div>
				<div class="flex font-josefin text-lg w-2/3 pb-5">{selected.description}</div>
				<div class="pb-5">
					<button class="btn btn-primary" on:click={runTitle}>Start</button>
					<button class="btn btn-primary" on:click={close}>Close</button>
				</div>
			</div>
		</div>
		<!--
	<div class="grid grid-cols-1">
		<img class="z-10 col-start-1 row-start-1 brightness-90 blur-[2px]" {src} alt="Bg" />
		<img class="z-20 col-start-1 row-start-1" src="footage/blank-large.png" alt="Alt" />
		<div class="z-30 col-start-1 row-start-1 pt-4 px-6">
			<div class="font-sofia-extra text-8xl">{selected.title}</div>
			<div class="flex pb-10 items-center">
				<div class="text-xs p-0.5 mr-2 border-2 h-fit rounded-md font-azaret">PAL</div>
				<div class="font-sofia-semi text-2xl flex">{selected.subtitle}</div>
			</div>
			<div class="flex font-josefin text-lg w-2/3 pb-5">{selected.description}</div>
			<div class="pb-5">
				<button class="btn btn-primary" on:click={runTitle}>Start</button>
				<button class="btn btn-primary" on:click={close}>Close</button>
			</div>
		</div>
	</div>
    -->
	</div>
{/if}
