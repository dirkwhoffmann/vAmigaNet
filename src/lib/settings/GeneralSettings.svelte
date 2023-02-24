<script lang="ts">
	import { onMount } from 'svelte';
	import { warpMode, theme, darkTheme, border, shaking } from '$lib/stores';
	import type { ActionEvent } from '$lib/Settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/Settings/ConfigItem.svelte';
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
			case Theme.default: newTheme = 'mytheme'; $darkTheme = true; break;
			case Theme.light: newTheme = 'light'; $darkTheme = true; break;
            case Theme.dark: newTheme = 'dark'; $darkTheme = true; break;
            case Theme.coffee: newTheme = 'coffee'; $darkTheme = false; break;
            case Theme.cupcake: newTheme = 'cupcake'; $darkTheme = false; break;
            case Theme.forest: newTheme = 'forest'; $darkTheme = true; break;
            case Theme.aqua: newTheme = 'aqua'; $darkTheme = false; break;
            case Theme.garden: newTheme = 'garden'; $darkTheme = true; break;
            case Theme.pastel: newTheme = 'pastel'; $darkTheme = false; break;
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
			selectedTag={$warpMode}
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
			selectedTag={$theme}
			on:select={themeAction}
			values={[
				{ name: 'Default', id: Theme.default },
				{ name: 'Light', id: Theme.light },
				{ name: 'Dark', id: Theme.dark },
				{ name: 'Coffee', id: Theme.coffee },
				{ name: 'Cupcake', id: Theme.cupcake },
				{ name: 'Forest', id: Theme.forest },
				{ name: 'Aqua', id: Theme.aqua },
				{ name: 'Garden', id: Theme.garden },
				{ name: 'Pastel', id: Theme.pastel },
			]}
		/>
		<ConfigItem
			name="Draw Canvas Border"
			selectedTag={$border}
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
			selectedTag={$shaking}
			on:select={shakingAction}
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
		/>
	</ConfigSection>
</div>
