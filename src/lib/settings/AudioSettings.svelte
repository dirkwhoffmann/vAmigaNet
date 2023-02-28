<script lang="ts">
	import { onMount } from 'svelte';
	import { proxy, amiga } from '$lib/stores';
	import type { ActionEvent } from '$lib/types';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/Settings/ConfigItem.svelte';

	let volume0: number, volume1: number, volume2: number, volume3: number;
	let volumeL: number, volumeR: number;
	let volumeStep: number, volumePoll: number, volumeInsert: number, volumeEject: number;

	onMount(() => {
		update();
	});

	function update() {
		volume0 = $amiga.getDriveConfig($proxy.OPT_AUDVOL, 0);
		volume1 = $amiga.getDriveConfig($proxy.OPT_AUDVOL, 1);
		volume2 = $amiga.getDriveConfig($proxy.OPT_AUDVOL, 2);
		volume3 = $amiga.getDriveConfig($proxy.OPT_AUDVOL, 3);
		volumeL = $amiga.getConfig($proxy.OPT_AUDVOLL);
		volumeR = $amiga.getConfig($proxy.OPT_AUDVOLR);
		volumeStep = $amiga.getDriveConfig($proxy.OPT_STEP_VOLUME, 0);
		volumePoll = $amiga.getDriveConfig($proxy.OPT_POLL_VOLUME, 0);
		volumeInsert = $amiga.getDriveConfig($proxy.OPT_INSERT_VOLUME, 0);
		volumeEject = $amiga.getDriveConfig($proxy.OPT_EJECT_VOLUME, 0);
	}

	function volumeAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure(event.detail.tag, event.detail.value);
		update();
	}

	function channelVolumeAction(event: CustomEvent<ActionEvent>) {
		$amiga.configureDrive($proxy.OPT_AUDVOL, event.detail.tag, event.detail.value);
		update();
	}
</script>

<div in:fade>
	<ConfigSection name="Speakers">
		<ConfigItem
			name="Left Speaker Volume"
			tag={$proxy.OPT_AUDVOLL}
			selectedTag={volumeL}
			on:select={volumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Right Speaker Volume"
			tag={$proxy.OPT_AUDVOLR}
			selectedTag={volumeR}
			on:select={volumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 0 Volume"
			tag={0}
			selectedTag={volume0}
			on:select={channelVolumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 1 Volume"
			tag={1}
			selectedTag={volume1}
			on:select={channelVolumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 2 Volume"
			tag={2}
			selectedTag={volume2}
			on:select={channelVolumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 3 Volume"
			tag={3}
			selectedTag={volume3}
			on:select={channelVolumeAction}
			min={0}
			max={100}
		/>
	</ConfigSection>
	<ConfigSection name="Drive Sounds">
		<ConfigItem
			name="Head Step Volume"
			tag={$proxy.OPT_STEP_VOLUME}
			selectedTag={volumeStep}
			on:select={volumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Poll Disk Volume"
			tag={$proxy.OPT_POLL_VOLUME}
			selectedTag={volumePoll}
			on:select={volumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Insert Disk Volume"
			tag={$proxy.OPT_INSERT_VOLUME}
			selectedTag={volumeInsert}
			on:select={volumeAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Eject Disk Volume"
			tag={$proxy.OPT_EJECT_VOLUME}
			selectedTag={volumeEject}
			on:select={volumeAction}
			min={0}
			max={100}
		/>
	</ConfigSection>
</div>
