<script lang="ts">
	import { onMount } from 'svelte';
	import { proxy, amiga } from '$lib/stores';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';

	let volume0: number, volume1: number, volume2: number, volume3: number;
	let volumeL: number, volumeR: number;

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
	}

	function volumeLAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_AUDVOLL, event.detail.value);
		update();
	}

	function volumeRAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_AUDVOLR, event.detail.value);
		update();
	}

	function volumeAction(event: CustomEvent<ActionEvent>) {
		$amiga.configureDrive($proxy.OPT_AUDVOL, event.detail.tag, event.detail.value);
		update();
	}
</script>

<div in:fade>
	<ConfigSection name="Volumes">
		<ConfigItem
			name="Left Speaker Volume"
			selection={volumeL}
			on:select={volumeLAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Right Speaker Volume"
			selection={volumeR}
			on:select={volumeRAction}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 0 Volume"
			selection={volume0}
			on:select={volumeAction}
			tag={0}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 1 Volume"
			selection={volume1}
			on:select={volumeAction}
			tag={1}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 2 Volume"
			selection={volume2}
			on:select={volumeAction}
			tag={2}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 3 Volume"
			selection={volume3}
			on:select={volumeAction}
			tag={3}
			min={0}
			max={100}
		/>
	</ConfigSection>
</div>
