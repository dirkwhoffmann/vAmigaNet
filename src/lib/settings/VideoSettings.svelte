<script lang="ts">
	import { onMount } from 'svelte';
	import { RenderMode } from '$lib/types';
	import { proxy, amiga } from '$lib/stores';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';
	import { renderMode, flickerWeight } from '$lib/stores';

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
		console.log("videoAction", event.detail.tag, event.detail.value);
		$amiga.configure(event.detail.tag, event.detail.value);
		update();
	}

	function renderModeAction(event: CustomEvent<ActionEvent>) {
		$renderMode = event.detail.value;
		update();
	}

	function flickerAction(event: CustomEvent<ActionEvent>) {
		$flickerWeight = event.detail.value;
		update();
	}
</script>

<div in:fade>
	<ConfigSection name="WebGL">
		<ConfigItem
			name="Render Mode"
			values={[
				{ name: 'Smooth', id: RenderMode.smooth },
				{ name: 'Pixelated', id: RenderMode.pixelated },
			]}
			selectedTag={$renderMode}
			on:select={renderModeAction}
		/>
	</ConfigSection>

	<ConfigSection name="Colors">
		<ConfigItem
			name="Palette"
			values={[
				{ name: 'Color', id: $proxy.PALETTE_COLOR },
				{ name: 'Black and White', id: $proxy.PALETTE_BLACK_WHITE },
				{ name: 'Paper White', id: $proxy.PALETTE_PAPER_WHITE },
				{ name: 'Green', id: $proxy.PALETTE_GREEN },
				{ name: 'Amber', id: $proxy.PALETTE_AMBER },
				{ name: 'Sepia', id: $proxy.PALETTE_SEPIA }
			]}
			selectedTag={palette}
			on:select={paletteAction}
		/>
		<ConfigItem
			name="Brightness"
			min={0}
			max={100}
			tag={$proxy.OPT_BRIGHTNESS}
			selectedTag={brightness}
			on:select={videoAction}
		/>
		<ConfigItem
			name="Contrast"
			min={0}
			max={100}
			tag={$proxy.OPT_CONTRAST}
			selectedTag={contrast}
			on:select={videoAction}
		/>
		<ConfigItem
			name="Saturation"
			min={0}
			max={100}
			tag={$proxy.OPT_SATURATION}
			selectedTag={saturation}
			on:select={videoAction}
		/>
	</ConfigSection>
	<ConfigSection name="Interlace">
		<ConfigItem
			name="Flicker Weight"
			min={0}
			max={100}
			tag={1000}
			selectedTag={$flickerWeight}
			on:select={flickerAction}
		/>
	</ConfigSection>

</div>
