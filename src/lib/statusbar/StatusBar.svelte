<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import DeviceInfo from '$lib/statusbar/DeviceInfo.svelte';
	import { dfConnected, dfMotor, dfWriting, dfUnsaved, dfCylinder } from '$lib/stores';

	const dispatch = createEventDispatcher<{ push: { sender: string } }>();
	const bg = 'bg-gradient-to-t from-gray-700 to-gray-600';

	function click(e: Event) {
		e.preventDefault();
		dispatch('push', { sender: (e.target as HTMLElement).id });
	}
</script>

<div class="z-50 relative flex h-8 mb-1">
	<div class="w-16 mr-1 flex justify-center {bg}">
		<button type="button" class="flex w-16 justify-center" id="vamigaButton" on:click={click}>
			<img class="h-full" src="icons/vamigaIcon.png" alt="vAmiga Icon" />
		</button>
	</div>
	<div class="{bg} border-0 border-red-500 flex grow">
		{#each Array(4) as _, i}
		{#if $dfConnected[i]}
			<DeviceInfo cylinder={$dfCylinder[i]} motor={$dfMotor[i]} writing={$dfWriting[i]} />
		{/if}
		{/each}
	</div>
</div>
