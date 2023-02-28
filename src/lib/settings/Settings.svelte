<script lang="ts">
	import { onMount } from 'svelte';
	import ConfigCategory from '$lib/Settings/ConfigCategory.svelte';
	import { fade } from 'svelte/transition';
	import GeneralSettings from '$lib/Settings/GeneralSettings.svelte';
	import MachineSettings from '$lib/Settings/MachineSettings.svelte';
	import VideoSettings from '$lib/Settings/VideoSettings.svelte';
	import AudioSettings from '$lib/Settings/AudioSettings.svelte';

	let active = 'GENERAL';

	onMount(() => {});
</script>
<div
	class="absolute top-0 left-0 w-full h-full flex overflow-auto text-base-content"
	transition:fade
>
	<div class="w-16 mr-1" />
	<div class="bg-base-100 opacity-100 bg-opacity-80 mt-0 p-4 grow h-full overflow-auto">
		<div class="font-sofia-extra">
			<div class="text-5xl">SETTINGS</div>
			<div class="float space-x-4 mb-6">
				<ConfigCategory name="GENERAL" {active} on:click={() => (active = 'GENERAL')} />
				<ConfigCategory name="MACHINE" {active} on:click={() => (active = 'MACHINE')} />
				<ConfigCategory name="VIDEO" {active} on:click={() => (active = 'VIDEO')} />
				<ConfigCategory name="AUDIO" {active} on:click={() => (active = 'AUDIO')} />
			</div>
		</div>
		{#if active == 'GENERAL'}
			<GeneralSettings />
		{:else if active == 'MACHINE'}
			<MachineSettings />
		{:else if active == 'VIDEO'}
			<VideoSettings />
		{:else if active == 'AUDIO'}
			<AudioSettings />
		{/if}
	</div>
</div>
