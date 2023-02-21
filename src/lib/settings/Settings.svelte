<script context="module" lang="ts">
	export type ActionEvent = { tag: number; value: number };
</script>

<script lang="ts">
	import { onMount } from 'svelte';
	import ConfigCategory from '$lib/settings/ConfigCategory.svelte';
	import { fade } from 'svelte/transition';
	import MachineSettings from '$lib/settings/MachineSettings.svelte';
	import VideoSettings from '$lib/settings/VideoSettings.svelte';
	import AudioSettings from '$lib/settings/AudioSettings.svelte';

	let category = 'machine';

	onMount(() => {});
</script>

<div class="absolute top-0 left-0 w-full h-full flex overflow-auto text-base-content" transition:fade>
	<div class="w-16 mr-1" />
	<div class="bg-base-100 opacity-75 mt-0 p-4 grow h-full overflow-auto">
		<div class="font-sofia-extra">
			<div class="text-5xl">SETTINGS</div>
			<div class="float space-x-4 mb-6">
				<ConfigCategory name="MACHINE" on:click={() => (category = 'machine')} />
				<ConfigCategory name="VIDEO" on:click={() => (category = 'video')} />
				<ConfigCategory name="AUDIO" on:click={() => (category = 'audio')} />
			</div>
		</div>
		{#if category == 'machine'}
			<MachineSettings />
		{:else if category == 'video'}
			<VideoSettings />
		{:else if category == 'audio'}
			<AudioSettings />
		{/if}
	</div>
</div>
