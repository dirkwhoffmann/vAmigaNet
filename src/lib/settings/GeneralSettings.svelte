<script lang="ts">
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { warpMode, theme, darkTheme, border, shaking } from '$lib/stores';
	import type { ActionEvent } from '$lib/types';
	import { MenuItem, Theme } from '$lib/types';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/Settings/ConfigItem.svelte';

	onMount(() => {
		update();
	});

	function update() {}

	function warpAction(event: CustomEvent<ActionEvent>) {
		console.log('warpAction');
		$warpMode = event.detail.value;
		update();
	}

	function themeAction(event: CustomEvent<ActionEvent>) {
		console.log('themeAction', $theme, event.detail.value);
		$theme = event.detail.value;
		let newTheme = '';
		switch ($theme) {
			case Theme.default:
				newTheme = 'mytheme';
				$darkTheme = true;
				break;
			case Theme.light:
				newTheme = 'light';
				$darkTheme = true;
				break;
			case Theme.dark:
				newTheme = 'dark';
				$darkTheme = true;
				break;
			case Theme.coffee:
				newTheme = 'coffee';
				$darkTheme = false;
				break;
			case Theme.cupcake:
				newTheme = 'cupcake';
				$darkTheme = false;
				break;
			case Theme.forest:
				newTheme = 'forest';
				$darkTheme = true;
				break;
			case Theme.aqua:
				newTheme = 'aqua';
				$darkTheme = false;
				break;
			case Theme.garden:
				newTheme = 'garden';
				$darkTheme = true;
				break;
			case Theme.pastel:
				newTheme = 'pastel';
				$darkTheme = false;
				break;
		}
		document.querySelector('html')!.setAttribute('data-theme', newTheme);
		update();
	}

	function borderAction(event: CustomEvent<ActionEvent>) {
		console.log('borderAction');
		$border = event.detail.value;
		update();
	}

	function shakingAction(event: CustomEvent<ActionEvent>) {
		console.log('shakingAction');
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
			items={[
				new MenuItem('During Disk Accesses', 0),
				new MenuItem('Never', 1),
				new MenuItem('Always', 2)
			]}
		/>
	</ConfigSection>
	<ConfigSection name="Appearance">
		<ConfigItem
			name="Color theme"
			selectedTag={$theme}
			on:select={themeAction}
			items={[
				new MenuItem('Default', Theme.default),
				new MenuItem('Light', Theme.light),
				new MenuItem('Dark', Theme.dark),
				new MenuItem('Coffee', Theme.coffee),
				new MenuItem('Cupcake', Theme.cupcake),
				new MenuItem('Forest', Theme.forest),
				new MenuItem('Aqua', Theme.aqua),
				new MenuItem('Garden', Theme.garden),
				new MenuItem('Pastel', Theme.pastel)
			]}
		/>
		<ConfigItem
			name="Draw Canvas Border"
			selectedTag={$border}
			on:select={borderAction}
			items={[new MenuItem('Yes', 1), new MenuItem('No', 0)]}
		/>
	</ConfigSection>
	<ConfigSection name="Peripherals">
		<ConfigItem
			name="Release Mouse by Shaking"
			selectedTag={$shaking}
			on:select={shakingAction}
			items={[new MenuItem('Yes', 1), new MenuItem('No', 0)]}
		/>
	</ConfigSection>
</div>
