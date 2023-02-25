<script lang="ts">
	import { onMount } from 'svelte';
	import { proxy, amiga, cpu, agnus } from '$lib/stores';
	import { darkTheme } from '$lib/stores';

	export let acceleration = 1.0;
	export let mhz = 0.0;
	export let emuFps = 0.0;
	export let gpuFps = 0.0;
	export let latchedTimestamp = 0.0;
	export let latchedCycle = 0.0;
	export let latchedEmuFrame = 0.0;
	export let latchedGpuFrame = 0.0;

	let open = false;
	let mode = 0;
	let value = '';
	$: color = $darkTheme ? 'text-gray-300' : 'text-black';
	
	let modes = [
		'Amiga Frequency',
		'Amiga Refresh Rate',
		'Host CPU Load',
		'Host GPU Refresh Rate',
		'Audio Buffer Fill Level'
	];
	// <div class="w-4">{@html selection == id ? '&#10003' : ''}</div>
	// const dispatch = createEventDispatcher<{push:{sender:string}}>();

	onMount(() => {
		console.log('Speedometer: onMount()');
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

	function action(e: MouseEvent, id: number) {
		e.preventDefault();
		// mode = Number((e.target as HTMLElement).id);
		mode = Number(id);
		open = false;
		redraw();
	}

	const defaultClass =
		'font-medium py-1 px-4 text-xs text-blue-200 bg-slate-600 hover:bg-slate-500';
</script>

<div class="flex h-8">
	<div class="h-full w-1 bg-black" />
	<div class="dropdown dropdown-end">
		<!-- Make DropDown work in Safari using the label / tabindex trick (see DaisyUI doc) -->
		<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
		<!-- svelte-ignore a11y-label-has-associated-control -->
		<label tabindex="0" class="flex w-20 text-xs h-full justify-center items-center {color}">{value}</label>
		<!-- svelte-ignore a11y-no-noninteractive-tabindex -->
		<ul
		tabindex="0" class="dropdown-content bg-accent text-accent-content menu menu-compact rounded p-0 text-sm w-64"
		>
			{#each modes as name, i}
				<li class="">
					<button on:click={(e) => action(e, i)}>
						<div class="w-4">{@html mode == i ? '&#10003' : ''}</div>
						{name}</button
					>
				</li>
			{/each}
		</ul>
	</div>
	
</div>
