<script lang="ts">
	import { onMount } from 'svelte';
	import { warpMode, theme, border, shaking } from '$lib/stores';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';
	import { Theme } from '$lib/types';

	onMount(() => {
		update();
	});

	function update() {
	}

	function warpAction(event: CustomEvent<ActionEvent>) {
        console.log("warpAction");
        $warpMode = event.detail.value; 
        update();
	}

	function themeAction(event: CustomEvent<ActionEvent>) {
        console.log("themeAction", $theme, event.detail.value);
        $theme = event.detail.value;
        let newTheme = '';
        switch ($theme) {
			case Theme.default: newTheme = 'mytheme'; break;
			case Theme.light: newTheme = 'light'; break;
            case Theme.dark: newTheme = 'dark'; break;
            case Theme.coffee: newTheme = 'coffee'; break;
        }
		document.querySelector('html')!.setAttribute('data-theme', newTheme);
        update();
	}

	function borderAction(event: CustomEvent<ActionEvent>) {
        console.log("borderAction");
        $border = event.detail.value;
        update();
	}

	function shakingAction(event: CustomEvent<ActionEvent>) {
        console.log("shakingAction");
        $shaking = event.detail.value;
        update();
	}
</script>

<div in:fade>
	<ConfigSection name="Warp mode">
		<ConfigItem
			name="Enable warp mode"
			selection={$warpMode}
			on:select={warpAction}
			values={[
				{ name: 'During Disk Accesses', id: 0 },
				{ name: 'Never', id: 1 },
				{ name: 'Always', id: 2 }
			]}
		/>
	</ConfigSection>
	<ConfigSection name="Appearance">
		<ConfigItem
			name="Color theme"
			selection={$theme}
			on:select={themeAction}
			values={[
				{ name: 'Default', id: Theme.default },
				{ name: 'Light', id: Theme.light },
				{ name: 'Dark', id: Theme.dark },
				{ name: 'Coffee', id: Theme.coffee }
			]}
		/>
		<ConfigItem
			name="Draw Canvas Border"
			selection={$border}
			on:select={borderAction}
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
		/>
	</ConfigSection>
	<ConfigSection name="Peripherals">
		<ConfigItem
			name="Release Mouse by Shaking"
			selection={$shaking}
			on:select={shakingAction}
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
		/>
	</ConfigSection>
</div>
