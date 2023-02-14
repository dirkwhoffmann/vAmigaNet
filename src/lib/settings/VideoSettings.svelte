<script lang="ts">
    
    import { onMount } from 'svelte';
    import { proxy, amiga } from '$lib/stores';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';

    let palette: number;

	onMount(() => {
		update();
	});

	function update() {
		palette = $amiga.getConfig($proxy.OPT_PALETTE);
	}

	function paletteAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_PALETTE, event.detail.value);
		update();
	}
</script>

<div transition:fade>
	<ConfigSection name="Monitor">
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
	</ConfigSection>
</div>
