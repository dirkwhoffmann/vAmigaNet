<script lang="ts">
	import { onMount } from 'svelte';
	import { RenderMode } from '$lib/types';
	import { proxy, amiga } from '$lib/stores';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';
	import { renderMode } from '$lib/stores';

	let palette: number;
	let brightness: number;
	let contrast: number;
	let saturation: number;

	onMount(() => {
		update();
	});

	function update() {
		palette = $amiga.getConfig($proxy.OPT_PALETTE);
		brightness = $amiga.getConfig($proxy.OPT_BRIGHTNESS);
		contrast = $amiga.getConfig($proxy.OPT_CONTRAST);
		saturation = $amiga.getConfig($proxy.OPT_SATURATION);
	}

	function paletteAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_PALETTE, event.detail.value);
		update();
	}

    function videoAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure(event.detail.tag, event.detail.value);
		update();
	}

	function renderModeAction(event: CustomEvent<ActionEvent>) {
		$renderMode = event.detail.value;
		update();
	}
</script>

<div in:fade>
	<ConfigSection name="WebGL">
		<ConfigItem
			name="Render Mode"
			selection={$renderMode}
			on:select={renderModeAction}
			values={[
				{ name: 'Smooth', id: RenderMode.smooth },
				{ name: 'Pixelated', id: RenderMode.pixelated },
			]}
		/>
	</ConfigSection>

	<ConfigSection name="Colors">
		<ConfigItem
			name="Palette"
			selection={palette}
			on:select={paletteAction}
			values={[
				{ name: 'Color', id: $proxy.PALETTE_COLOR },
				{ name: 'Black and White', id: $proxy.PALETTE_BLACK_WHITE },
				{ name: 'Paper White', id: $proxy.PALETTE_PAPER_WHITE },
				{ name: 'Green', id: $proxy.PALETTE_GREEN },
				{ name: 'Amber', id: $proxy.PALETTE_AMBER },
				{ name: 'Sepia', id: $proxy.PALETTE_SEPIA }
			]}
		/>
		<ConfigItem
			name="Brightness"
			selection={brightness}
			on:select={videoAction}
			tag={$proxy.OPT_BRIGHTNESS}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Contrast"
			selection={contrast}
			on:select={videoAction}
			tag={$proxy.OPT_CONTRAST}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Saturation"
			selection={saturation}
			on:select={videoAction}
			tag={$proxy.OPT_SATURATION}
			min={0}
			max={100}
		/>
	</ConfigSection>
</div>
