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
		dfProtected
	} from '$lib/stores';

	let speedometer: Speedometer;

	const dispatch = createEventDispatcher<{ push: { sender: string } }>();
	const bg = 'bg-gradient-to-t from-gray-700 to-gray-600';

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
		<button type="button" class="flex w-16 h-full justify-center" id="vamigaButton" on:click={click}>
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
	<Speedometer bind:this={speedometer} />
</div>
