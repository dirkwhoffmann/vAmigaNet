<script lang="ts">
	import type { ActionEvent } from '$lib/types';
	import { onMount } from 'svelte';
	import { proxy, amiga, cpu, agnus } from '$lib/stores';
	import { darkTheme } from '$lib/stores';
	import Menu from '$lib/Widgets/Menu.svelte';
	import { MenuItem } from '$lib/types';

	export let acceleration = 1.0;
	export let mhz = 0.0;
	export let emuFps = 0.0;
	export let gpuFps = 0.0;
	export let latchedTimestamp = 0.0;
	export let latchedCycle = 0.0;
	export let latchedEmuFrame = 0.0;
	export let latchedGpuFrame = 0.0;

	let mode = 0;
	let value = '';
	$: color = $darkTheme ? 'text-gray-300' : 'text-black';

	let items: MenuItem[] = [
		new MenuItem('Amiga Frequency', 0),
		new MenuItem('Amiga Refresh Rate', 1),
		new MenuItem('Host CPU Load', 2),
		new MenuItem('Host GPU Refresh Rate', 3),
		new MenuItem('Audio Buffer Fill Level', 4)
	];
	items[0].isSelected = true;

	onMount(() => {
		latchedTimestamp = Date.now();
	});

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
				acceleration = $amiga.getConfig($proxy.OPT_CPU_OVERCLOCKING);
				if (acceleration == 0) acceleration = 1;
				value = (mhz * acceleration).toFixed(2) + ' MHz';
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

	function selectAction(event: CustomEvent<ActionEvent>) {
		event.preventDefault();
		mode = event.detail.value;
		items.forEach(function (item) {
			item.isSelected = item.tag == mode;
		});

		// Force component to refresh
		items = items;
		redraw();
	}
</script>

<div class="flex h-8">
	<div class="h-full w-1 bg-black" />
	<Menu
		{items}
		on:select={selectAction}
		dropdownStyle="dropdown-end"
		listStyle="menu menu-compact rounded text-sm w-64"
	>
		<div class="flex w-20 text-xs text-primary-content h-full justify-center items-center">{value}</div>
	</Menu>
</div>
