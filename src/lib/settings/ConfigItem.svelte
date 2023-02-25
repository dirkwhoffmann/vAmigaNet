<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import GoInfo from 'svelte-icons/go/GoInfo.svelte';
	import GiPadlock from 'svelte-icons/gi/GiPadlock.svelte';
	import type { ActionEvent } from '$lib/Settings/Settings.svelte';
	import DropDown from '$lib/Widgets/DropDown.svelte';
	import Slider from '$lib/Widgets/Slider.svelte';

	export let name = '';
	export let values = [{ name: '???', id: 0 }];
	export let min = 0;
	export let max = 0;
	export let locked = false;
	export let info = false;
	export let tag = 0;
	export let selectedTag = 0;

	const infoDispatcher = createEventDispatcher<{ info: ActionEvent }>();

	$: opac = locked ? 'opacity-50' : '';

	const infoAction = (e: Event) => {
		e.preventDefault();
		infoDispatcher('info', { tag: tag, value: selectedTag });
	};

</script>

<div class="py-0.5 px-0">
	<div class="w-full flex text-xl space-x-1 justify-between items-center">
		<div class="border-0 bg-primary w-full h-12 flex grow overflow-hidden">
			<div
				class="w-full border-0 text-xl {opac} text-primary-content flex items-center justify-between"
			>
				<div class="border-0 mx-2 flex grow overflow-hidden whitespace-nowrap">{name}</div>
			</div>
		</div>
		<div
			class="border-0 bg-primary w-20 h-12 flex items-center justify-center {locked
				? ''
				: 'hidden'}"
		>
			<button class="h-7 w-7 text-primary-content {opac}"><GiPadlock /></button>
		</div>
		<div
			class="border-0 bg-primary w-20 h-12 flex items-center justify-center {info ? '' : 'hidden'}"
		>
			<button class="h-7 w-7 text-primary-content {opac}" on:click={infoAction}><GoInfo /></button>
		</div>
		<div class="border-0 bg-primary h-12">
			{#if min == max}
				<DropDown {values} {locked} {tag} {selectedTag} on:select />
			{:else}
				<Slider {min} {max} {locked} {tag} {selectedTag} on:select />
			{/if}
		</div>
	</div>
</div>
