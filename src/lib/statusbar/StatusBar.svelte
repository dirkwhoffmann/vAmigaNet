<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import DeviceInfo from '$lib/statusbar/DeviceInfo.svelte';
	import Speedometer from '$lib/statusbar/Speedometer.svelte';
	import BarBox from '$lib/statusbar/BarBox.svelte';
	import {
		dfConnected,
		dfHasDisk,
		dfCylinder,
		dfMotor,
		dfWriting,
		dfUnsaved,
		dfProtected,
		warp,
		debugMode,
		halted,
		muted,
	} from '$lib/stores';
	import StatusIcon from './StatusIcon.svelte';
	import WarpControl from './WarpControl.svelte';

	let speedometer: Speedometer;

	$: muteIcon = $muted || $warp; 
	$: debugIcon = $debugMode; 
	$: haltIcon = $halted; 

	$: console.log("muted = ", muted);
	$: console.log("warp = ", warp);
	$: console.log("debugMode = ", debugMode);
	$: console.log("halted = ", halted);
	$: console.log("muteIcon = ", muteIcon);
	$: console.log("debugIcon = ", debugIcon);
	$: console.log("haltIcon = ", haltIcon);

	const dispatch = createEventDispatcher<{ push: { sender: string } }>();
	// const bg = 'bg-gradient-to-t from-gray-700 to-gray-600';
	const bg = 'bg-gradient-to-t from-primary to-primary/80';

	export function update(animationFrame: number, now: DOMHighResTimeStamp) {
		if (speedometer) {
			speedometer.update(animationFrame, now);
		}
	}

	function click(e: Event) {
		e.preventDefault();
		dispatch('push', { sender: (e.target as HTMLElement).id });
	}
</script>

<div class="z-50 relative flex h-8 mb-1 {bg}">
	<BarBox>
		<button
			type="button"
			class="flex w-16 h-full justify-center"
			id="vamigaButton"
			on:click={click}
		>
			<img class="h-full" src="icons/vamigaIcon.png" alt="vAmiga Icon" />
		</button>
	</BarBox>
	<div class="border-0 border-red-500 flex grow">
		{#each Array(4) as _, i}
			{#if $dfConnected[i]}
				<DeviceInfo
					disk={$dfHasDisk[i]}
					cyl={$dfCylinder[i]}
					motor={$dfMotor[i]}
					writing={$dfWriting[i]}
					unsaved={$dfUnsaved[i]}
					wp={$dfProtected[i]}
				/>
			{/if}
		{/each}
	</div>
	{#if haltIcon}
		<StatusIcon src="icons/halt.png" />
	{/if}
	{#if debugIcon}
		<StatusIcon src="icons/debug.png" />
	{/if}
	{#if muteIcon}
		<StatusIcon src="icons/mute.png" />
	{/if}
	<WarpControl />
	<Speedometer bind:this={speedometer} />
</div>
