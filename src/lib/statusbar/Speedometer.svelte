<script lang="ts">
	import { onMount } from 'svelte';
	import { cpu, agnus } from '$lib/stores';
	import BarBox from './BarBox.svelte';
	import { Button, Dropdown, DropdownItem, Chevron } from 'flowbite-svelte';

	export let acceleration = 1.0;
	export let mhz = 0.0;
	export let emuFps = 0.0;
	export let gpuFps = 0.0;
	export let latchedTimestamp = 0.0;
	export let latchedCycle = 0.0;
	export let latchedEmuFrame = 0.0;
	export let latchedGpuFrame = 0.0;
	export let counter = 0;

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
            switch (mode) {
                case 0: value = mhz.toFixed(2) + " MHz"; break;
                case 1: value = emuFps.toFixed(0) + " Hz"; break; 
                // case 2: value = "TODO"; break; 
                case 3: value = gpuFps.toFixed(0) + " Hz"; break; 
                // case 4: value = "TODO"; break; 
                default: value = "---";
            }
		}
		// Keep values
		latchedTimestamp = timestamp;
		latchedCycle = cycle;
		latchedEmuFrame = emuFrame;
		latchedGpuFrame = gpuFrame;
	}

	function mhzAction(e: MouseEvent) {
		e.preventDefault();
		mode = 0;
	}

	function fpsAction(e: MouseEvent) {
		e.preventDefault();
		mode = 1;
	}

	function cpuAction(e: MouseEvent) {
		e.preventDefault();
		mode = 2;
	}

	function gpuAction(e: MouseEvent) {
		e.preventDefault();
		mode = 3;
	}

	function audAction(e: MouseEvent) {
		e.preventDefault();
		mode = 4;
	}

	const defaultClass =
		'font-medium py-1 px-4 text-xs text-blue-200 bg-slate-600 hover:bg-slate-500';
</script>

<div class="flex h-8">
	<div class="h-full w-1 bg-black" />
	<div class="flex w-20 text-xs h-full justify-center items-center {color}">{value}</div>
	<Dropdown frameClass="!bg-slate-600">
		<DropdownItem on:click={(e) => mhzAction(e)} {defaultClass}>Amiga Frequency</DropdownItem>
		<DropdownItem on:click={(e) => fpsAction(e)} {defaultClass}>Amiga Refresh Rate</DropdownItem>
		<!--
		<DropdownItem on:click={(e) => cpuAction(e)} {defaultClass}>
            Host GPU Load
        </DropdownItem>
        -->
		<DropdownItem on:click={(e) => gpuAction(e)} {defaultClass}>Host GPU Refresh Rate</DropdownItem>
		<DropdownItem on:click={(e) => audAction(e)} {defaultClass}
			>Audio Buffer Fill Level</DropdownItem
		>
	</Dropdown>
</div>
