<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import FaLock from 'svelte-icons/fa/FaLock.svelte';
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
	export let selection = 0;
	export let tag = 0;

	let dropdownOpen = false;
	let stepValue = 2.5;

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

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

	const sliderAction = (e: Event) => {
		e.preventDefault();
		dispatch('select', { tag: tag, value: e.target!.value });
	};
</script>

<div class="py-0.5 px-0">
	<div class="w-full flex text-xl space-x-1 justify-between items-center">
		<div class="border-0 bg-blue-400/20 w-full h-12 flex flex-col justify-center">
			<div class="p-4 text-xl text-blue-200 flex items-center">
				{#if locked}
					<div class="border-0 mr-3 h-6 w-6 opacity-50"><FaLock /></div>
					<div class="border-0 opacity-50">{name}</div>
				{:else}
					<div class="border-0">{name}</div>
				{/if}
			</div>
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
						</button
					>
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
