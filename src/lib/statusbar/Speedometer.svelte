<script lang="ts">
	import { onMount } from 'svelte';
	import { amiga, cpu, agnus } from '$lib/stores';
	import BarBox from './BarBox.svelte';
	import { Button, Dropdown, DropdownItem, Chevron } from 'flowbite-svelte';
	import { draw } from 'svelte/transition';

	export let acceleration = 1.0;
	export let mhz = 0.0;
	export let emuFps = 0.0;
	export let gpuFps = 0.0;
	export let latchedTimestamp = 0.0;
	export let latchedCycle = 0.0;
	export let latchedEmuFrame = 0.0;
	export let latchedGpuFrame = 0.0;
	export let counter = 0;

	let open = false;
	let mode = 0;
	let value = '';
	$: color = 'text-gray-300'; // (value > 6 && value < 8) ? "text-green-300" : "text-red-300";

	// const dispatch = createEventDispatcher<{push:{sender:string}}>();

	onMount(() => {
		console.log('Speedometer: onMount()');
		latchedTimestamp = Date.now();
	});

	function click(e: Event) {
		e.preventDefault();
		// dispatch('push', { sender: (e.target as HTMLElement).id });
	}

	export function update(animationFrame: number, now: DOMHighResTimeStamp) {
		if (animationFrame % 10 != 0) return;

		let timestamp = Date.now();
		let elapsedTime = (timestamp - latchedTimestamp) / 1000;

		let cycle = $cpu.getClock();
		let emuFrame = $agnus.frameCount();
		let gpuFrame = animationFrame;

		// Measure clock frequency
		if (cycle >= latchedCycle) {
			const elapsedCycles = (cycle - latchedCycle) / 1000000;
			const alpha = 0.5;
			mhz = alpha * (elapsedCycles / elapsedTime) + (1 - alpha) * mhz;
		}

		// Measure emulator frames per second
		if (animationFrame % 25 == 0 && emuFrame >= latchedEmuFrame) {
			const elapsedFrames = emuFrame - latchedEmuFrame;
			const alpha = 0.9;
			emuFps = alpha * (elapsedFrames / elapsedTime) + (1 - alpha) * emuFps;
		}

		if (animationFrame % 25 == 0 && gpuFrame >= latchedGpuFrame) {
			// Measure GPU frames per second
			const elapsedFrames = gpuFrame - latchedGpuFrame;
			const alpha = 0.9;
			gpuFps = alpha * (elapsedFrames / elapsedTime) + (1 - alpha) * gpuFps;
		}

		if (animationFrame % 25 == 0) {
			redraw();
		}

		// Keep values
		latchedTimestamp = timestamp;
		latchedCycle = cycle;
		latchedEmuFrame = emuFrame;
		latchedGpuFrame = gpuFrame;
	}

	function redraw() {
		switch (mode) {
			case 0:
				value = mhz.toFixed(2) + ' MHz';
				break;
			case 1:
				value = emuFps.toFixed(0) + ' Hz';
				break;
			case 2:
				value = $amiga.cpuLoad() + '%';
				break;
			case 3:
				value = gpuFps.toFixed(0) + ' Hz';
				break;
			case 4:
				value = $amiga.audioFillLevel() + '%';
				break;
			default:
				value = '---';
				break;
		}
	}

	function action(e: MouseEvent) {
		e.preventDefault();
		mode = Number((e.target as HTMLElement).id);
		open = false;
		redraw();
	}

	const defaultClass =
		'font-medium py-1 px-4 text-xs text-blue-200 bg-slate-600 hover:bg-slate-500';
</script>

<div class="flex h-8">
	<div class="h-full w-1 bg-black" />
	<div class="flex w-20 text-xs h-full justify-center items-center {color}">{value}</div>
	<Dropdown frameClass="!bg-slate-600" bind:open>
		<DropdownItem id="0" on:click={(e) => action(e)} {defaultClass}>Amiga Frequency</DropdownItem>
		<DropdownItem id="1" on:click={(e) => action(e)} {defaultClass}>Amiga Refresh Rate</DropdownItem
		>
		<DropdownItem id="2" on:click={(e) => action(e)} {defaultClass}>Host CPU Load</DropdownItem>
		<DropdownItem id="3" on:click={(e) => action(e)} {defaultClass}
			>Host GPU Refresh Rate</DropdownItem
		>
		<DropdownItem id="4" on:click={(e) => action(e)} {defaultClass}
			>Audio Buffer Fill Level</DropdownItem
		>
	</Dropdown>
</div>
