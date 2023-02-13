<script lang="ts">
	import { onMount } from 'svelte';
	import { cpu, agnus } from '$lib/stores';
	import BarBox from './BarBox.svelte';
    import { Progressbar, Chevron } from 'flowbite-svelte';

	export let acceleration = 1.0;
	export let mhz = 0.0;
	export let emuFps = 0.0;
	export let gpuFps = 0.0;
	export let latchedTimestamp = 0.0;
	export let latchedCycle = 0.0;
	export let latchedEmuFrame = 0.0;
	export let latchedGpuFrame = 0.0;
	export let counter = 0;

	let value = 0;
    $: color = "text-gray-300"; // (value > 6 && value < 8) ? "text-green-300" : "text-red-300";

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
		if (animationFrame % 8 != 0) return;

		let timestamp = Date.now();
		let elapsedTime = timestamp - latchedTimestamp;

		let cycle = $cpu.getClock();
		let emuFrame = $agnus.frameCount();
		let gpuFrame = 0; // TODO

		// Measure clock frequency
		if (cycle >= latchedCycle) {
			const elapsedCycles = (cycle - latchedCycle) / 1000;
			const alpha = 0.5;
			mhz = alpha * (elapsedCycles / elapsedTime) + (1 - alpha) * mhz;
		}

		// Measure emulator frames per second
		if (animationFrame % 32 == 0 && emuFrame >= latchedEmuFrame) {
			const elapsedFrames = emuFrame - latchedEmuFrame;
			const alpha = 0.9;
			emuFps = alpha * (elapsedFrames / elapsedTime) + (1 - alpha) * emuFps;
		}

		if (animationFrame % 32 == 0 && gpuFrame >= latchedGpuFrame) {
			// Measure GPU frames per second
			const elapsedFrames = gpuFrame - latchedGpuFrame;
			const alpha = 0.9;
			gpuFps = alpha * (elapsedFrames / elapsedTime) + (1 - alpha) * gpuFps;
		}

		if (animationFrame % 32 == 0) {
			value = mhz;
        }
		// Keep values
		latchedTimestamp = timestamp;
		latchedCycle = cycle;
		latchedEmuFrame = emuFrame;
		latchedGpuFrame = gpuFrame;
	}
</script>

<div class="flex h-8">
	<div class="h-full w-1 bg-black" />
	<div class="flex w-20 text-xs h-full justify-center items-center {color}">
		{value.toFixed(2)} MHz
	</div>
</div>
