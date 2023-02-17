<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import FaLock from 'svelte-icons/fa/FaLock.svelte';
	import GoInfo from 'svelte-icons/go/GoInfo.svelte';
	import GiPadlock from 'svelte-icons/gi/GiPadlock.svelte'
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import Chevron from './Chevron.svelte';

	export let name = '';
	export let displayAs = '';
	export let values = [{ name: '???', id: 0 }];
	export let min = 0;
	export let max = 0;
	// export let continous = true;
	export let locked = false;
	export let info = false;
	export let selection = 0;
	export let tag = 0;

	let dropdownOpen = false;
	let stepValue = 2.5;

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	$: opac = locked ? 'opacity-50' : '';

	$: displayName = displayedName(selection);

	function displayedName(tag: number): string {
		if (displayAs != '') return displayAs;
		if (min != max) return tag.toString();
		for (const value of values) {
			if (value.id == tag) return value.name;
		}
		return '???';
	}

	const handleClick = (e: MouseEvent, value: number) => {
		e.preventDefault();
		dropdownOpen = false;
		console.log('Click: id = ' + value + ' tag = ' + tag);
		dispatch('select', { tag: tag, value: value });
	};

	const infoAction = (e: Event) => {
		e.preventDefault();
		console.log('infoAction');
		dispatch('info', { tag: tag, value: e.target!.value });
	};

	const sliderAction = (e: Event) => {
		e.preventDefault();
		dispatch('select', { tag: tag, value: e.target!.value });
	};
</script>

<div class="py-0.5 px-0">
	<div class="w-full flex text-xl space-x-1 justify-between items-center">
		<div class="border-0 bg-blue-400/20 w-full h-12 flex grow overflow-hidden">
			<div class="w-full border-0 text-xl {opac} text-blue-200 flex items-center justify-between">
				<div class="border-0 mx-2 flex grow overflow-hidden whitespace-nowrap">{name}
				</div>
				<!--
				<div class="flex mr-2 border-0 items-center {opac}">
					<button class="h-6 w-6 mr-1 {locked ? '' : 'hidden'}"><FaLock /></button>
					<button class="h-7 w-7 {info ? '' : 'hidden'}" on:click={infoAction}><GoInfo /></button>
				</div>
				-->
			</div>
		</div>
		<div class="border-0 bg-blue-400/20 w-20 h-12 flex items-center justify-center {locked ? '' : 'hidden'}">
			<button class="h-7 w-7 text-blue-200 {opac}"><GiPadlock /></button>
		</div>
		<div class="border-0 bg-blue-400/20 w-20 h-12 flex items-center justify-center {info ? '' : 'hidden'}">
			<button class="h-7 w-7 text-blue-200 {opac}" on:click={infoAction}><GoInfo /></button>
		</div>
			<div class="border-0 bg-blue-400/20 h-12">
			{#if locked}
				<button
					class="btn w-[18rem] border-0 rounded-none text-xl font-normal opacity-50 text-blue-200 hover:bg-slate-600 bg-transparent"
					>{displayName}</button
				>
			{:else}
				<div class="dropdown dropdown-end">
					<button
						class="btn w-[18rem] border-0 rounded-none text-xl font-normal text-blue-200 hover:bg-slate-600 bg-transparent"
						><Chevron>{displayName}</Chevron>
					</button>
					{#if min != max}
						<ul class="dropdown-content menu w-[18rem]">
							<input
								type="range"
								style="--range-shdw: none"
								on:input={(e) => sliderAction(e)}
								on:click={(e) => console.log('Click')}
								min="0"
								max="100"
								value={selection}
								class="range h-12 px-4 rounded-none bg-blue-200"
							/>
						</ul>
					{:else}
						<ul class="dropdown-content menu p-2 text-xl text-blue-200 bg-slate-600 w-[18rem]">
							{#each values as { name, id }, i}
								<li class="" id={id.toString()}>
									<button on:click={(e) => handleClick(e, id)}
										><div class="w-4">{@html selection == id ? '&#10003' : ''}</div>
										{name}</button
									>
								</li>
							{/each}
						</ul>
					{/if}
				</div>
			{/if}
		</div>
	</div>
</div>
