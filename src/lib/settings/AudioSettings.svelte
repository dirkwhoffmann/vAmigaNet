<script lang="ts">
    
    import { onMount } from 'svelte';
    import { proxy, amiga } from '$lib/stores';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { fade } from 'svelte/transition';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';

    let volumeL: number;
    let volumeR: number;

	onMount(() => {
		update();
	});

	function update() {
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

</script>

<div transition:fade>
	<ConfigSection name="Amiga Audio">
		<ConfigItem
			name="Left Master Volume"
			selection={volumeL}
			on:select={volumeLAction}
            min={0}
            max={100}
		/>
		<ConfigItem
			name="Right Master Volume"
			selection={volumeR}
			on:select={volumeRAction}
            min={0}
            max={100}
		/>
	</ConfigSection>
</div>
